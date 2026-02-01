#pragma once

#include "Mustard/Application/Subprogram.h++"

namespace CRMuSR2::SimCRMu {

class SimCRMu : public Mustard::Application::Subprogram {
public:
    SimCRMu();
    auto Main(int argc, char* argv[]) const -> int override;
};

} // namespace CRMuSR2::SimCRMu
