#include "SimCRMu/Action/ActionInitialization.h++"
#include "SimCRMu/Detector/DetectorConstruction.h++"
#include "SimCRMu/Analysis.h++"
#include "SimCRMu/RunManager.h++"
#include "CRMuSR2/Simulation/Physics/StandardPhysicsList.h++"

#include "Mustard/Env/BasicEnv.h++"

#include "muc/utility"

namespace CRMuSR2::SimCRMu {

RunManager::RunManager() :
    MPIRunManager{},
    fAnalysis{std::make_unique_for_overwrite<Analysis>()} {

    SetUserInitialization(new StandardPhysicsList);

    const auto detectorConstruction{new DetectorConstruction};
    detectorConstruction->SetCheckOverlaps(Mustard::Env::VerboseLevelReach<'I'>());
    SetUserInitialization(detectorConstruction);

    SetUserInitialization(new ActionInitialization);
}

RunManager::~RunManager() = default;

} // namespace CRMuSR2::SimCRMu
