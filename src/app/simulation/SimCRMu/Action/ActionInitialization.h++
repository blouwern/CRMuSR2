#pragma once

#include "Mustard/Env/Memory/PassiveSingleton.h++"

#include "G4VUserActionInitialization.hh"

namespace CRMuSR2::SimCRMu::inline Action {

class ActionInitialization final : public Mustard::Env::Memory::PassiveSingleton<ActionInitialization>,
                                   public G4VUserActionInitialization {
public:
    ActionInitialization();

    auto Build() const -> void override;
};

} // namespace CRMuSR2::SimCRMu::inline Action
