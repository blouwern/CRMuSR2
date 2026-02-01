#include "CRMuSR2/Simulation/Action/NeutrinoKillerSteppingAction.h++"

namespace CRMuSR2::inline Simulation::inline Action {

NeutrinoKillerSteppingAction<void>::NeutrinoKillerSteppingAction() :
    NeutrinoKillerSteppingAction<NeutrinoKillerSteppingAction<void>>{this} {}

} // namespace CRMuSR2::inline Simulation::inline Action
