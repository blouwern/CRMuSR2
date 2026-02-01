#include "CRMuSR2/Simulation/Physics/StandardPhysicsList.h++"
#include "CRMuSR2/Simulation/Physics/StandardPhysicsListMessenger.h++"

#include "G4UIcmdWithoutParameter.hh"
#include "G4UnitsTable.hh"

namespace CRMuSR2::inline Simulation::inline Physics {

StandardPhysicsListMessenger::StandardPhysicsListMessenger() :
    SingletonMessenger{},
    fUseRadioactiveDecayPhysics{},
    fUseOpticalPhysics{} {

    fUseRadioactiveDecayPhysics = std::make_unique<G4UIcmdWithoutParameter>("/CRMuSR2/Physics/UseRadioactiveDecayPhysics", this);
    fUseRadioactiveDecayPhysics->SetGuidance("If set, the G4RadioactiveDecayPhysics will be registered in the physics list.");
    fUseRadioactiveDecayPhysics->AvailableForStates(G4State_PreInit);

    fUseOpticalPhysics = std::make_unique<G4UIcmdWithoutParameter>("/CRMuSR2/Physics/UseOpticalPhysics", this);
    fUseOpticalPhysics->SetGuidance("If set, the G4OpticalPhysics will be registered in the physics list.");
    fUseOpticalPhysics->AvailableForStates(G4State_PreInit);
}

StandardPhysicsListMessenger::~StandardPhysicsListMessenger() = default;

auto StandardPhysicsListMessenger::SetNewValue(G4UIcommand* command, G4String) -> void {
    if (command == fUseRadioactiveDecayPhysics.get()) {
        Deliver<StandardPhysicsListBase>([&](auto&& r) {
            r.UseRadioactiveDecayPhysics();
        });
    } else if (command == fUseOpticalPhysics.get()) {
        Deliver<StandardPhysicsListBase>([&](auto&& r) {
            r.UseOpticalPhysics();
        });
    }
}

} // namespace CRMuSR2::inline Simulation::inline Physics
