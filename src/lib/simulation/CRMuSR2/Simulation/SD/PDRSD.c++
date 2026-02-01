#include "CRMuSR2/Detector/Description/PDRScintillator.h++"
#include "CRMuSR2/Simulation/SD/PDRPMSD.h++"
#include "CRMuSR2/Simulation/SD/PDRSD.h++"

#include "Mustard/Data/Tuple.h++"
#include "Mustard/IO/PrettyLog.h++"

#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4OpticalPhoton.hh"
#include "G4ParticleDefinition.hh"
#include "G4RotationMatrix.hh"
#include "G4SDManager.hh"
#include "G4Step.hh"
#include "G4StepPoint.hh"
#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"
#include "G4TwoVector.hh"
#include "G4VProcess.hh"
#include "G4VTouchable.hh"

#include "muc/algorithm"
#include "muc/numeric"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <functional>
#include <iterator>
#include <numeric>
#include <ranges>
#include <string_view>
#include <tuple>
#include <utility>
#include <vector>

namespace CRMuSR2::inline Simulation::inline SD {

PDRSD::PDRSD(const G4String& sdName, const PDRPMSD* PDRPMSD) :
    // Mustard::NonMoveableBase{},
    G4VSensitiveDetector{sdName},
    fPDRPMSD{PDRPMSD},
    fEnergyDepositionThreshold{},
    fSplitHit{},
    fHitsCollection{} {
    PDRPMSD->NOpticalPhotonHit();
    collectionName.insert(sdName + "HC");

    const auto& pdrSci{Detector::Description::PDRScintillator::Instance()};
    assert(pdrSci.PSScintillationEnergyBin().size() == pdrSci.PSScintillationComponent1().size());
    std::vector<double> dE(pdrSci.PSScintillationEnergyBin().size());
    muc::ranges::adjacent_difference(pdrSci.PSScintillationEnergyBin(), dE.begin());
    std::vector<double> spectrum(pdrSci.PSScintillationComponent1().size());
    muc::ranges::adjacent_difference(pdrSci.PSScintillationEnergyBin(), spectrum.begin(), muc::midpoint<double>);
    const auto integral{std::inner_product(next(spectrum.cbegin()), spectrum.cend(), next(dE.cbegin()), 0.)};
    std::vector<double> meanE(pdrSci.PSScintillationEnergyBin().size());
    muc::ranges::adjacent_difference(pdrSci.PSScintillationEnergyBin(), meanE.begin(), muc::midpoint<double>);
    std::ranges::transform(spectrum, meanE, spectrum.begin(), std::multiplies{});
    fEnergyDepositionThreshold = std::inner_product(next(spectrum.cbegin()), spectrum.cend(), next(dE.cbegin()), 0.) / integral;

    // # per layer * 2 layers per wall * 4 wall
    fSplitHit.reserve(pdrSci.NScintillatorPerLayer() * 2 * 4);
}

auto PDRSD::Initialize(G4HCofThisEvent* hitsCollectionOfThisEvent) -> void {
    fHitsCollection = new PDRSimHitCollection{SensitiveDetectorName, collectionName[0]};
    const auto hitsCollectionID{G4SDManager::GetSDMpointer()->GetCollectionID(fHitsCollection)};
    hitsCollectionOfThisEvent->AddHitsCollection(hitsCollectionID, fHitsCollection);
}

auto PDRSD::ProcessHits(G4Step* theStep, G4TouchableHistory*) -> G4bool {
    const auto& step{*theStep};
    const auto& track{*step.GetTrack()};
    const auto& particle{*track.GetDefinition()};

    if (&particle == G4OpticalPhoton::Definition()) {
        return false;
    }

    const auto eDep{step.GetTotalEnergyDeposit()};

    if (eDep < fEnergyDepositionThreshold) {
        return false;
    }
    assert(eDep > 0);

    const auto& preStepPoint{*step.GetPreStepPoint()};
    const auto& touchable{*preStepPoint.GetTouchable()};

    // replica number list 0:Scintillator, 1:VirtualWallBox
    const auto nSciPerLayer{Detector::Description::PDRScintillator::Instance().NScintillatorPerLayer()};
    const auto wallID{touchable.GetReplicaNumber(1)};
    const auto sciLocalID{touchable.GetReplicaNumber(0)};
    const auto sciID{wallID * nSciPerLayer * 2 + sciLocalID};

    // calculate (Ek0, p0)
    const auto vertexEk{track.GetVertexKineticEnergy()};
    const auto vertexMomentum{track.GetVertexMomentumDirection() * std::sqrt(vertexEk * (vertexEk + 2 * particle.GetPDGMass()))};
    // track creator process
    const auto creatorProcess{track.GetCreatorProcess()};
    // new a hit
    const auto& hit{fSplitHit[sciID].emplace_back(std::make_unique_for_overwrite<PDRSimHit>())};
    Get<"EvtID">(*hit) = G4EventManager::GetEventManager()->GetConstCurrentEvent()->GetEventID();
    Get<"HitID">(*hit) = -1; // to be determined
    Get<"DetID">(*hit) = sciID;
    Get<"t">(*hit) = preStepPoint.GetGlobalTime();
    Get<"Edep">(*hit) = eDep;
    // Get<"nOptPho">(*hit) = -1; // to be determined
    Get<"x">(*hit) = preStepPoint.GetPosition() - touchable.GetTranslation();
    Get<"Ek">(*hit) = preStepPoint.GetKineticEnergy();
    Get<"p">(*hit) = preStepPoint.GetMomentum();
    Get<"TrkID">(*hit) = track.GetTrackID();
    Get<"PDGID">(*hit) = particle.GetPDGEncoding();
    Get<"t0">(*hit) = track.GetGlobalTime() - track.GetLocalTime();
    Get<"x0">(*hit) = track.GetVertexPosition();
    Get<"Ek0">(*hit) = vertexEk;
    Get<"p0">(*hit) = vertexMomentum;
    *Get<"CreatProc">(*hit) = creatorProcess ? std::string_view{creatorProcess->GetProcessName()} : "|0>";

    return true;
}

auto PDRSD::EndOfEvent(G4HCofThisEvent*) -> void {
    fHitsCollection->GetVector()->reserve(
        muc::ranges::accumulate(fSplitHit, 0,
                                [](auto&& count, auto&& cellHit) {
                                    return count + cellHit.second.size();
                                }));

    // Digitization: merge hits within scintillation time window to simulate detector response
    for (auto&& [sciID, splitHit] : fSplitHit) {
        switch (splitHit.size()) {
        case 0:
            muc::unreachable();
        case 1: {
            // Single hit: no clustering needed
            auto& hit{splitHit.front()};
            assert(Get<"DetID">(*hit) == sciID);
            fHitsCollection->insert(hit.release());
        } break;
        default: {
            // Multiple hits: cluster by scintillation decay time window
            const auto scintillationTimeConstant1{Detector::Description::PDRScintillator::Instance().PSScintillationTimeConstant1()};
            assert(scintillationTimeConstant1 >= 0);
            // Sort hits by time for sequential window scanning
            muc::timsort(splitHit,
                         [](const auto& hit1, const auto& hit2) {
                             return Get<"t">(*hit1) < Get<"t">(*hit2);
                         });
            // Iterate through hits, grouping those within each time window into pulses
            std::ranges::subrange cluster{splitHit.begin(), splitHit.begin()};
            while (cluster.end() != splitHit.end()) {
                // Define time window: [tFirst, tFirst + τ]
                const auto tFirst{*Get<"t">(**cluster.end())};
                const auto windowClosingTime{tFirst + scintillationTimeConstant1};
                if (tFirst == windowClosingTime and // Notice: bad numeric with huge Get<"t">(**clusterFirst)!
                    scintillationTimeConstant1 != 0) [[unlikely]] {
                    Mustard::MasterPrintWarning(fmt::format("A huge time ({}) completely rounds off the time resolution ({})", tFirst, scintillationTimeConstant1));
                }
                // Collect all hits within this time window
                cluster = {cluster.end(), std::ranges::find_if_not(cluster.end(), splitHit.end(),
                                                                   [&windowClosingTime](const auto& hit) {
                                                                       return Get<"t">(*hit) <= windowClosingTime;
                                                                   })};
                // Select hit with smallest TrkID as representative (typically the primary particle but not necessarily)
                auto& topHit{*std::ranges::min_element(cluster,
                                                       [](const auto& hit1, const auto& hit2) {
                                                           return Get<"TrkID">(*hit1) < Get<"TrkID">(*hit2);
                                                       })};
                // Sum energy depositions from all hits in this pulse
                assert(Get<"DetID">(*topHit) == sciID);
                for (const auto& hit : cluster) {
                    if (hit == topHit) {
                        continue;
                    }
                    Get<"Edep">(*topHit) += Get<"Edep">(*hit);
                }
                fHitsCollection->insert(topHit.release());
            }
        } break;
        }
    }
    fSplitHit.clear();

    muc::timsort(*fHitsCollection->GetVector(),
                 [](const auto& hit1, const auto& hit2) {
                     return std::tie(Get<"TrkID">(*hit1), Get<"t">(*hit1)) <
                            std::tie(Get<"TrkID">(*hit2), Get<"t">(*hit2));
                 });

    for (int hitID{}; auto&& hit : *fHitsCollection->GetVector()) {
        Get<"HitID">(*hit) = hitID++;
    }

//     if (fPDRPMSD) {
//         auto nHit{fPDRPMSD->NOpticalPhotonHit()};
//         auto nHitOnEachSiPM{fPDRPMSD->NOpticalPhotonOnEachSiPM()};
//         for (auto&& hit : std::as_const(*fHitsCollection->GetVector())) {
//             if (not nHit.empty()) {
//                 Get<"nOptPho">(*hit) = nHit.at(Get<"DetID">(*hit));
//             } else {
//                 Get<"nOptPho">(*hit) = 0;
//             }
//         }
//     }
}

} // namespace CRMuSR2::inline Simulation::inline SD
