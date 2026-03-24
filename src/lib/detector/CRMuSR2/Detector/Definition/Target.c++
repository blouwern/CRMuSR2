#include "CRMuSR2/Detector/Definition/Target.h++"
#include "CRMuSR2/Detector/Description/Target.h++"

#include "Mustard/Detector/CADMesh.h++"

#include "G4Box.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"

namespace CRMuSR2::Detector::Definition {

auto Target::Construct(G4bool checkOverlaps) -> void {
    const auto& target{Description::Target::Instance()};
    const auto& mesh{Mustard::Detector::CADMesh::TessellatedMesh::FromSTL(target.STLFilePath())};
    // const auto& mesh{Mustard::Detector::CADMesh::TessellatedMesh::FromOBJ(target.OBJFilePath())};
    const auto solid{mesh->GetSolid()};
    const auto logic{Make<G4LogicalVolume>(
        solid,
        G4NistManager::Instance()->FindOrBuildMaterial("G4_Cu"),
        target.Name())};
    Make<G4PVPlacement>(
        G4Transform3D(G4Translate3D(0, 0, target.TargetElevation())),
        logic,
        target.Name(),
        Mother().LogicalVolume(),
        false,
        0,
        checkOverlaps);
}

} // namespace CRMuSR2::Detector::Definition
