#include "SimCRMu/Messenger/AnalysisMessenger.h++"

#include "SimCRMu/Action/PrimaryGeneratorAction.h++"
#include "SimCRMu/Action/TrackingAction.h++"
#include "SimCRMu/Analysis.h++"

#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIdirectory.hh"

#include <string_view>

namespace CRMuSR2::SimCRMu::inline Messenger {

AnalysisMessenger::AnalysisMessenger() :
    SingletonMessenger{},
    fDirectory{},
    fSavePrimaryVertexData{},
    fSaveDecayVertexData{},
    fCoincidenceWithPDR{} {

    fDirectory = std::make_unique<G4UIdirectory>("/CRMuSR2/Analysis/");
    fDirectory->SetGuidance("CRMuSR2::SimCRMu::Analysis controller.");

    fSavePrimaryVertexData = std::make_unique<G4UIcmdWithABool>("/CRMuSR2/Analysis/SavePrimaryVertexData", this);
    fSavePrimaryVertexData->SetGuidance("Save primary vertex data if enabled.");
    fSavePrimaryVertexData->SetParameterName("mode", false);
    fSavePrimaryVertexData->AvailableForStates(G4State_Idle);

    fSaveDecayVertexData = std::make_unique<G4UIcmdWithABool>("/CRMuSR2/Analysis/SaveDecayVertexData", this);
    fSaveDecayVertexData->SetGuidance("Save decay vertex data if enabled.");
    fSaveDecayVertexData->SetParameterName("mode", false);
    fSaveDecayVertexData->AvailableForStates(G4State_Idle);

    fCoincidenceWithPDR = std::make_unique<G4UIcmdWithABool>("/CRMuSR2/Analysis/CoincidenceWithPDR", this);
    fCoincidenceWithPDR->SetGuidance("Coincidence with PDR if enabled.");
    fCoincidenceWithPDR->SetParameterName("mode", false);
    fCoincidenceWithPDR->AvailableForStates(G4State_Idle);
}

AnalysisMessenger::~AnalysisMessenger() = default;

auto AnalysisMessenger::SetNewValue(G4UIcommand* command, G4String value) -> void {
    if (command == fSavePrimaryVertexData.get()) {
        Deliver<PrimaryGeneratorAction>([&](auto&& r) {
            r.SavePrimaryVertexData(fSavePrimaryVertexData->GetNewBoolValue(value));
        });
    } else if (command == fSaveDecayVertexData.get()) {
        Deliver<TrackingAction>([&](auto&& r) {
            r.SaveDecayVertexData(fSaveDecayVertexData->GetNewBoolValue(value));
        });
    } else if (command == fCoincidenceWithPDR.get()) {
        Deliver<Analysis>([&](auto&& r) {
            r.CoincidenceWithPDR(fCoincidenceWithPDR->GetNewBoolValue(value));
        });
    }
}

} // namespace CRMuSR2::SimCRMu::inline Messenger
