#include "CRMuSR2/Detector/Description/PDRScintillator.h++"
#include "CRMuSR2/Simulation/SD/PDRPMSD.h++"

#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4OpticalPhoton.hh"
#include "G4SDManager.hh"
#include "G4Step.hh"
#include "G4StepPoint.hh"
#include "G4Track.hh"
#include "G4VTouchable.hh"

#include <algorithm>
#include <cassert>

namespace CRMuSR2::inline Simulation::inline SD {
using namespace CRMuSR2::Detector::Description;

PDRPMSD::PDRPMSD(const G4String& sdName) :
    // Mustard::NonMoveableBase{},
    G4VSensitiveDetector{sdName},
    fHit{},
    fHitsCollection{} {
    collectionName.insert(sdName + "HC");
    const auto& pdrSci{Detector::Description::PDRScintillator::Instance()};
    // # per layer * 2 layers per wall * 4 wall * 2 SiPM per scinitllator
    fHit.reserve(pdrSci.NScintillatorPerLayer() * 2 * 4 * 2);
}

auto PDRPMSD::Initialize(G4HCofThisEvent* hitsCollectionOfThisEvent) -> void {
    fHit.clear(); // clear at the begin of event allows PDRSD to get optical photon counts at the end of event
    fHitsCollection = new PDRPMSimHitCollection(SensitiveDetectorName, collectionName[0]);
    auto hitsCollectionID{G4SDManager::GetSDMpointer()->GetCollectionID(fHitsCollection)};
    hitsCollectionOfThisEvent->AddHitsCollection(hitsCollectionID, fHitsCollection);
}

auto PDRPMSD::ProcessHits(G4Step* theStep, G4TouchableHistory*) -> G4bool {
    const auto& step{*theStep};
    const auto& track{*step.GetTrack()};
    const auto& particle{*track.GetDefinition()};

    if (&particle != G4OpticalPhoton::Definition()) {
        return false;
    }

    step.GetTrack()->SetTrackStatus(fStopAndKill);

    const auto& preStepPoint{*step.GetPreStepPoint()};
    const auto& touchable{*preStepPoint.GetTouchable()};

    // replica number: 0:SiPMSensor, 1:SiPMBox, 2:VirtualWallBox
    const auto nSciPerLayer{PDRScintillator::Instance().NScintillatorPerLayer()};
    const auto channelID{nSciPerLayer * 2 * touchable.GetReplicaNumber(2) + touchable.GetReplicaNumber(1)};
    // new a hit
    auto hit{std::make_unique_for_overwrite<PDRPMSimHit>()};
    Get<"EvtID">(*hit) = G4EventManager::GetEventManager()->GetConstCurrentEvent()->GetEventID();
    // Get<"HitID">(*hit) = -1; // to be determined
    Get<"ChID">(*hit) = channelID;
    Get<"t">(*hit) = preStepPoint.GetGlobalTime();
    fHit[channelID].emplace_back(std::move(hit));
    return true;
}

auto PDRPMSD::EndOfEvent(G4HCofThisEvent*) -> void {
    for (/*int hitID{};*/
         auto&& [channelID, hitOfUnit] : fHit) {
        for (auto&& hit : hitOfUnit) {
            // Get<"HitID">(*hit) = hitID++;
            assert(Get<"ChID">(*hit) == channelID);
            fHitsCollection->insert(hit.release());
            // Notice: One PDRPMSimHit unique_ptr released, but pointer object remains
        }
    }
}

auto PDRPMSD::NOpticalPhotonHit() const -> std::unordered_map<int, int> {
    std::unordered_map<int, int> nHit;
    for (auto&& [channelID, hit] : fHit) {
        if (hit.size() > 0) {
            nHit[channelID] = hit.size();
        }
    }
    return nHit;
}

} // namespace CRMuSR2::inline Simulation::inline SD
