#include "SimCRMu/Action/RunAction.h++"
#include "SimCRMu/Analysis.h++"

#include "G4Run.hh"

namespace CRMuSR2::SimCRMu::inline Action {

RunAction::RunAction() :
    PassiveSingleton{this},
    G4UserRunAction{} {}

auto RunAction::BeginOfRunAction(const G4Run* run) -> void {
    Analysis::Instance().RunBeginAction(run->GetRunID());
}

auto RunAction::EndOfRunAction(const G4Run* run) -> void {
    Analysis::Instance().RunEndAction(run->GetRunID());
}

} // namespace CRMuSR2::SimCRMu::inline Action
