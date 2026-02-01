#pragma once

#include "CRMuSR2/Data/SimVertex.h++"

#include "Mustard/Data/Tuple.h++"
#include "Mustard/Env/Memory/PassiveSingleton.h++"

#include "SimCRMu/Messenger/AnalysisMessenger.h++"

#include "G4UserTrackingAction.hh"

#include "muc/ptrvec"

namespace CRMuSR2::SimCRMu::inline Action {

class TrackingAction final : public Mustard::Env::Memory::PassiveSingleton<TrackingAction>,
                             public G4UserTrackingAction {
public:
    TrackingAction();

    auto PostUserTrackingAction(const G4Track* track) -> void override;

    auto SaveDecayVertexData() const -> auto { return fSaveDecayVertexData; }
    auto SaveDecayVertexData(bool val) -> void { fSaveDecayVertexData = val; }

    auto ClearDecayVertexData() -> void { return fDecayVertexData.clear(); }
    auto DecayVertexData() const -> const auto& { return fDecayVertexData; }

private:
    auto UpdateDecayVertexData(const G4Track& track) -> void;

private:
    bool fSaveDecayVertexData;

    muc::unique_ptrvec<Mustard::Data::Tuple<Data::SimDecayVertex>> fDecayVertexData;

    AnalysisMessenger::Register<TrackingAction> fMessengerRegister;
};

} // namespace CRMuSR2::SimCRMu::inline Action
