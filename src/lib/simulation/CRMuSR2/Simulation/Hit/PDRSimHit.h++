#pragma once

#include "CRMuSR2/Data/ScintillatorDataModel.h++"

#include "Mustard/Data/Tuple.h++"
#include "Mustard/Geant4X/Memory/UseG4Allocator.h++"

#include "G4THitsCollection.hh"
#include "G4VHit.hh"

namespace CRMuSR2::inline Simulation::inline Hit {

class PDRSimHit final : public Mustard::Geant4X::UseG4Allocator<PDRSimHit>,
                        public G4VHit,
                        public Data::SimScintillatorHit {};

using PDRSimHitCollection = G4THitsCollection<PDRSimHit>;
} // namespace CRMuSR2::inline Simulation::inline Hit
