#include "CRMuSR2/Simulation/Hit/PDRPMSimHit.h++"
#include "CRMuSR2/Simulation/Hit/PDRSimHit.h++"
#include "SimCRMu/Analysis.h++"

#include "Mustard/Env/MPIEnv.h++"
#include "Mustard/Geant4X/Utility/ConvertGeometry.h++"
#include "Mustard/Parallel/ProcessSpecificPath.h++"

#include "SimCRMu/Action/PrimaryGeneratorAction.h++"
#include "SimCRMu/Action/TrackingAction.h++"

#include "TFile.h"
#include "TMacro.h"

#include "fmt/core.h"

#include <algorithm>
#include <optional>
#include <stdexcept>
namespace CRMuSR2::SimCRMu {
Analysis::Analysis() :
    AnalysisBase{this},
    fCoincidenceWithPDR{true},
    fPrimaryVertexOutput{},
    fDecayVertexOutput{},
    fPDRSimHitOutput{},
    fPDRPMSimHitOutput{},
    fPrimaryVertex{},
    fDecayVertex{},
    fPDRSimHit{},
    fPDRPMSimHit{},
    fMessengerRegister{this} {}

auto Analysis::RunBeginUserAction(int runID) -> void {
    if (PrimaryGeneratorAction::Instance().SavePrimaryVertexData()) {
        fPrimaryVertexOutput.emplace(fmt::format("G4Run{}/SimPrimaryVertex", runID));
    }
    if (TrackingAction::Instance().SaveDecayVertexData()) {
        fDecayVertexOutput.emplace(fmt::format("G4Run{}/SimDecayVertex", runID));
    }
    fPDRSimHitOutput.emplace(fmt::format("G4Run{}/PDRSimHit", runID));
    fPDRPMSimHitOutput.emplace(fmt::format("G4Run{}/PDRPMSimHit", runID));
}

auto Analysis::EventEndUserAction() -> void {
    const auto PDRPassed{not fCoincidenceWithPDR or fPDRSimHit == nullptr or fPDRSimHit->size() > 0};
    if (PDRPassed) {
        if (fPrimaryVertex and fPrimaryVertexOutput) {
            fPrimaryVertexOutput->Fill(*fPrimaryVertex);
        }
        if (fDecayVertex and fDecayVertexOutput) {
            fDecayVertexOutput->Fill(*fDecayVertex);
        }
        if (fPDRSimHit) {
            fPDRSimHitOutput->Fill(*fPDRSimHit);
        }
        if (fPDRPMSimHit) {
            fPDRPMSimHitOutput->Fill(*fPDRPMSimHit);
        }
    }
    fPrimaryVertex = {};
    fDecayVertex = {};
    fPDRSimHit = {};
    fPDRPMSimHit = {};
}

auto Analysis::RunEndUserAction(int) -> void {
    // write data
    if (fPrimaryVertexOutput) {
        fPrimaryVertexOutput->Write();
    }
    if (fDecayVertexOutput) {
        fDecayVertexOutput->Write();
    }
    if (fPDRSimHitOutput) {
        fPDRSimHitOutput->Write();
    }
    if (fPDRPMSimHitOutput) {
        fPDRPMSimHitOutput->Write();
    }
    // reset output
    fPrimaryVertexOutput.reset();
    fDecayVertexOutput.reset();
    fPDRSimHitOutput.reset();
    fPDRPMSimHitOutput.reset();
}

} // namespace CRMuSR2::SimCRMu