#include "SimCRMu/Action/ActionInitialization.h++"
#include "SimCRMu/Action/EventAction.h++"
#include "SimCRMu/Action/PrimaryGeneratorAction.h++"
#include "SimCRMu/Action/RunAction.h++"
#include "SimCRMu/Action/TrackingAction.h++"

namespace CRMuSR2::SimCRMu::inline Action {

ActionInitialization::ActionInitialization() :
    PassiveSingleton{this},
    G4VUserActionInitialization{} {}

auto ActionInitialization::Build() const -> void {
    SetUserAction(new PrimaryGeneratorAction);
    SetUserAction(new RunAction);
    SetUserAction(new EventAction);
    SetUserAction(new TrackingAction);
    // SetUserAction(new NeutrinoKillerSteppingAction<>);
}

} // namespace CRMuSR2::SimCRMu::inline Action
