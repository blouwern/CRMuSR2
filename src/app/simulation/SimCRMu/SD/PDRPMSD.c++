#include "SimCRMu/Analysis.h++"
#include "SimCRMu/SD/PDRPMSD.h++"

namespace CRMuSR2::SimCRMu::inline SD {

auto PDRPMSD::EndOfEvent(G4HCofThisEvent* hc) -> void {
    Simulation::PDRPMSD::EndOfEvent(hc);
    Analysis::Instance().SubmitPDRPMSimHC(*fHitsCollection->GetVector());
}

} // namespace CRMuSR2::SimCRMu::inline SD
