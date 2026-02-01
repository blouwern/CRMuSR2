#include "SimCRMu/Detector/DetectorConstruction.h++"
#include "SimCRMu/DefaultMacro.h++"
#include "SimCRMu/RunManager.h++"
#include "SimCRMu/SimCRMu.h++"

#include "Mustard/CLI/Geant4CLI.h++"
#include "Mustard/CLI/Module/DetectorDescriptionModule.h++"
#include "Mustard/Env/Geant4Env.h++"
#include "Mustard/Geant4X/Interface/MPIExecutive.h++"

namespace CRMuSR2::SimCRMu {

SimCRMu::SimCRMu() :
    Subprogram{"SimCRMu", "Simulation of cosmic ray events."} {}

auto SimCRMu::Main(int argc, char* argv[]) const -> int {
    Mustard::CLI::Geant4CLI<Mustard::CLI::DetectorDescriptionModule<DetectorConstruction::ProminentDescription>> cli;
    Mustard::Env::Geant4Env env{argc, argv, cli};

    RunManager runManager;
    Mustard::Geant4X::MPIExecutive{}.StartSession(cli, defaultMacro);

    return EXIT_SUCCESS;
}

} // namespace CRMuSR2::SimCRMu
