#pragma once

#include "CRMuSR2/Data/PhotosensorDataModel.h++"

#include "Mustard/Data/Tuple.h++"
#include "Mustard/Geant4X/Memory/UseG4Allocator.h++"

#include "G4THitsCollection.hh"
#include "G4VHit.hh"

namespace CRMuSR2::inline Simulation::inline Hit {

class PDRPMSimHit final : public Mustard::Geant4X::UseG4Allocator<PDRPMSimHit>,
                          public G4VHit,
                          public Data::SimPhotosensorHit {};

using PDRPMSimHitCollection = G4THitsCollection<PDRPMSimHit>;
} // namespace CRMuSR2::inline Simulation::inline Hit
