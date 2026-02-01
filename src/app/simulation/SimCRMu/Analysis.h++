#pragma once

#include "CRMuSR2/Data/PhotosensorDataModel.h++"
#include "CRMuSR2/Data/ScintillatorDataModel.h++"
#include "CRMuSR2/Data/SimVertex.h++"
#include "SimCRMu/Messenger/AnalysisMessenger.h++"

#include "Mustard/Data/Output.h++"
#include "Mustard/Data/Tuple.h++"
#include "Mustard/Simulation/AnalysisBase.h++"

#include "muc/ptrvec"

#include "gsl/gsl"

#include <filesystem>
#include <utility>
#include <vector>

class TFile;

namespace CRMuSR2::inline Simulation::inline Hit {
class PDRSimHit;
class PDRPMSimHit;
} // namespace CRMuSR2::inline Simulation::inline Hit

namespace CRMuSR2::SimCRMu {

class Analysis final : public Mustard::Simulation::AnalysisBase<Analysis, "SimCRMu"> {
public:
    Analysis();

    auto SubmitPrimaryVertexData(const std::vector<std::unique_ptr<Mustard::Data::Tuple<Data::SimPrimaryVertex>>>& data) -> void { fPrimaryVertex = &data; }
    auto SubmitDecayVertexData(const std::vector<std::unique_ptr<Mustard::Data::Tuple<Data::SimDecayVertex>>>& data) -> void { fDecayVertex = &data; }
    auto SubmitPDRSimHC(const std::vector<gsl::owner<PDRSimHit*>>& hc) -> void { fPDRSimHit = &hc; }
    auto SubmitPDRPMSimHC(const std::vector<gsl::owner<PDRPMSimHit*>>& hc) -> void { fPDRPMSimHit = &hc; }
    auto CoincidenceWithPDR(bool var) -> void { fCoincidenceWithPDR = var; }

    auto RunBeginUserAction(int runID) -> void override;
    auto EventEndUserAction() -> void override;
    auto RunEndUserAction(int) -> void override;

private:
    bool fCoincidenceWithPDR;

    std::optional<Mustard::Data::Output<Data::SimPrimaryVertex>> fPrimaryVertexOutput;
    std::optional<Mustard::Data::Output<Data::SimDecayVertex>> fDecayVertexOutput;
    std::optional<Mustard::Data::Output<Data::SimScintillatorHitModel>> fPDRSimHitOutput;
    std::optional<Mustard::Data::Output<Data::SimPhotosensorHitModel>> fPDRPMSimHitOutput;

    const std::vector<std::unique_ptr<Mustard::Data::Tuple<Data::SimPrimaryVertex>>>* fPrimaryVertex;
    const std::vector<std::unique_ptr<Mustard::Data::Tuple<Data::SimDecayVertex>>>* fDecayVertex;
    const std::vector<gsl::owner<PDRSimHit*>>* fPDRSimHit;
    const std::vector<gsl::owner<PDRPMSimHit*>>* fPDRPMSimHit;

    AnalysisMessenger::Register<Analysis> fMessengerRegister;
};

} // namespace CRMuSR2::SimCRMu
