#include "SimCRMu/Analysis.h++"
#include "SimCRMu/SD/PDRSD.h++"

namespace CRMuSR2::SimCRMu::inline SD {

auto PDRSD::EndOfEvent(G4HCofThisEvent* hc) -> void {
    Simulation::PDRSD::EndOfEvent(hc);
    Analysis::Instance().SubmitPDRSimHC(*fHitsCollection->GetVector());
}

} // namespace CRMuSR2::SimCRMu::inline SD
