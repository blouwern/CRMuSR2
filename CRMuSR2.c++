#include "SimCRMu/SimCRMu.h++"

#include "Mustard/Application/SubprogramLauncher.h++"

auto main(int argc, char* argv[]) -> int {
    Mustard::Application::SubprogramLauncher launcher;
    launcher.AddSubprogram<CRMuSR2::SimCRMu::SimCRMu>();
    return launcher.LaunchMain(argc, argv);
}
