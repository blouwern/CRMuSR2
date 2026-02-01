#include "SimCRMu/Action/EventAction.h++"
#include "SimCRMu/Action/PrimaryGeneratorAction.h++"
#include "SimCRMu/Action/TrackingAction.h++"
#include "SimCRMu/Analysis.h++"

#include "G4Event.hh"

namespace CRMuSR2::SimCRMu::inline Action {

EventAction::EventAction() :
    PassiveSingleton{this},
    G4UserEventAction{} {}

auto EventAction::BeginOfEventAction(const G4Event*) -> void {
    if (auto& trackingAction{TrackingAction::Instance()};
        trackingAction.SaveDecayVertexData()) {
        trackingAction.ClearDecayVertexData();
    }
}

auto EventAction::EndOfEventAction(const G4Event*) -> void {
    auto& analysis{Analysis::Instance()};
    if (const auto& trackingAction{TrackingAction::Instance()};
        trackingAction.SaveDecayVertexData()) {
        analysis.SubmitDecayVertexData(trackingAction.DecayVertexData());
    }
    analysis.EventEndAction();
}

} // namespace CRMuSR2::SimCRMu::inline Action
