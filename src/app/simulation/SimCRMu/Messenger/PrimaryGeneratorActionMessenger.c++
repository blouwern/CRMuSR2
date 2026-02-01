#include "SimCRMu/Action/PrimaryGeneratorAction.h++"
#include "SimCRMu/Messenger/PrimaryGeneratorActionMessenger.h++"

#include "G4UIcmdWithoutParameter.hh"

namespace CRMuSR2::SimCRMu::inline Messenger {

PrimaryGeneratorActionMessenger::PrimaryGeneratorActionMessenger() :
    SingletonMessenger{},
    fSwitchToGPSX{},
    fSwitchToEcoMug{} {

    fSwitchToGPSX = std::make_unique<G4UIcmdWithoutParameter>("/CRMuSR2/Generator/SwitchToGPSX", this);
    fSwitchToGPSX->SetGuidance("If set then the G4GeneralParticleSource will be used.");
    fSwitchToGPSX->AvailableForStates(G4State_Idle);

    fSwitchToEcoMug = std::make_unique<G4UIcmdWithoutParameter>("/CRMuSR2/Generator/SwitchToEcoMug", this);
    fSwitchToEcoMug->SetGuidance("If set then the EcoMug generator will be used.");
    fSwitchToEcoMug->AvailableForStates(G4State_Idle);
}

PrimaryGeneratorActionMessenger::~PrimaryGeneratorActionMessenger() = default;

void PrimaryGeneratorActionMessenger::SetNewValue(G4UIcommand* command, G4String) {
    if (command == fSwitchToGPSX.get()) {
        Deliver<PrimaryGeneratorAction>([&](auto&& r) {
            r.SwitchToGPSX();
        });
    } else if (command == fSwitchToEcoMug.get()) {
        Deliver<PrimaryGeneratorAction>([&](auto&& r) {
            r.SwitchToEcoMug();
        });
    }
}

} // namespace CRMuSR2::SimCRMu::inline Messenger
