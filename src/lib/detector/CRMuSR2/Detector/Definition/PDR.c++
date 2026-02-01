#include "CRMuSR2/Detector/Definition/PDR.h++"
#include "CRMuSR2/Detector/Description/PDRScintillator.h++"
#include "CRMuSR2/Detector/Description/PDRSiPM.h++"
#include "CRMuSR2/Detector/Description/PDRSupport.h++"

#include "Mustard/Detector/CADMesh.h++"
#include "Mustard/Utility/LiteralUnit.h++"
#include "Mustard/Utility/MathConstant.h++"

#include "G4Box.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"

#include "muc/math"

#include <algorithm>

using namespace Mustard::MathConstant;
using namespace Mustard::LiteralUnit::Density;
using namespace Mustard::LiteralUnit::Length;

namespace CRMuSR2::Detector::Definition {

auto PDR::DefineMateiral() -> void {

    const auto nistManager{G4NistManager::Instance()};
    const auto& scintillator{Description::PDRScintillator::Instance()};
    const auto [minPhotonEnergy, maxPhotonEnergy]{std::ranges::minmax(scintillator.PSScintillationEnergyBin())};
    // SiPM material
    fSi = nistManager->FindOrBuildMaterial("G4_Si");
    // steel material
    fSteel = nistManager->FindOrBuildMaterial("G4_STAINLESS-STEEL");
    // coupler material
    const auto hydrogenElement{nistManager->FindOrBuildElement("H")};
    const auto carbonElement{nistManager->FindOrBuildElement("C")};
    const auto oxygenElement{nistManager->FindOrBuildElement("O")};
    const auto siliconElement{nistManager->FindOrBuildElement("Si")};
    fSiliconeGrease = new G4Material("PDRSiliconeGrease", 1.06_g_cm3, 4, kStateLiquid);
    fSiliconeGrease->AddElement(carbonElement, 2);
    fSiliconeGrease->AddElement(hydrogenElement, 6);
    fSiliconeGrease->AddElement(oxygenElement, 1);
    fSiliconeGrease->AddElement(siliconElement, 1);
    const auto siliconeGreasePropertiesTable{new G4MaterialPropertiesTable};
    siliconeGreasePropertiesTable->AddProperty("RINDEX", {minPhotonEnergy, maxPhotonEnergy}, {1.46, 1.46}); // EJ-550
    siliconeGreasePropertiesTable->AddProperty("ABSLENGTH", {minPhotonEnergy, maxPhotonEnergy}, {100_cm, 100_cm});
    fSiliconeGrease->SetMaterialPropertiesTable(siliconeGreasePropertiesTable);
    // SiPM window material
    fEpoxy = new G4Material("epoxy", 1.18_g_cm3, 3, kStateSolid);
    fEpoxy->AddElement(carbonElement, 0.7362);
    fEpoxy->AddElement(hydrogenElement, 0.0675);
    fEpoxy->AddElement(oxygenElement, 0.1963);
    const auto epoxyPropertiesTable{new G4MaterialPropertiesTable};
    epoxyPropertiesTable->AddProperty("RINDEX", {minPhotonEnergy, maxPhotonEnergy}, {1.59, 1.59}); // microft-30032-smt
    fEpoxy->SetMaterialPropertiesTable(epoxyPropertiesTable);
    // plastic scintillator material
    fPlasticScintillator = new G4Material("Polyvinyl_toluene", 1.023_g_cm3, 2, kStateSolid);
    fPlasticScintillator->AddElement(carbonElement, 9);
    fPlasticScintillator->AddElement(hydrogenElement, 10);
    const auto plasticScintillatorPropertiesTable{new G4MaterialPropertiesTable};
    plasticScintillatorPropertiesTable->AddProperty("RINDEX", {minPhotonEnergy, maxPhotonEnergy}, {1.58, 1.58});
    plasticScintillatorPropertiesTable->AddProperty("ABSLENGTH", {minPhotonEnergy, maxPhotonEnergy}, {380_cm, 380_cm});
    plasticScintillatorPropertiesTable->AddProperty("SCINTILLATIONCOMPONENT1", scintillator.PSScintillationEnergyBin(), scintillator.PSScintillationComponent1());
    plasticScintillatorPropertiesTable->AddConstProperty("SCINTILLATIONYIELD", scintillator.PSScintillationYield());
    plasticScintillatorPropertiesTable->AddConstProperty("SCINTILLATIONTIMECONSTANT1", scintillator.PSScintillationTimeConstant1());
    plasticScintillatorPropertiesTable->AddConstProperty("RESOLUTIONSCALE", scintillator.PSResolutionScale());
    fPlasticScintillator->SetMaterialPropertiesTable(plasticScintillatorPropertiesTable);

    // air
    fAir = nistManager->FindOrBuildMaterial("G4_AIR");
    const auto airPropertiesTable{new G4MaterialPropertiesTable};
    airPropertiesTable->AddProperty("RINDEX", "Air");
    fAir->SetMaterialPropertiesTable(airPropertiesTable);
}

auto PDR::Construct(bool checkOverlaps) -> void {
    DefineMateiral();
    int nSupport{4};
    const auto& scintillator{Description::PDRScintillator::Instance()};
    const auto& support{Description::PDRSupport::Instance()};
    const auto& sipm{Description::PDRSiPM::Instance()};

    const auto sipmWidth{sipm.PDRSiPMWidth()};
    const auto sipmSensorWidth{sipm.PDRSiPMSensorWidth()};
    const auto sipmSensorThickness{sipm.PDRSiPMSensorThickness()};
    const auto sipmResinThickness{sipm.PDRSiPMResinThickness()};
    const auto sipmCouplerThickness{sipm.PDRSiPMCouplerThickness()};
    const auto supportThickness{support.PDRSupportThickness()};
    const auto supportHeight{support.PDRSupportHeight()};
    const auto scintillatorThickness{scintillator.PDRScintillatorThickness()};
    const auto scintillatorWidth{scintillator.PDRScintillatorWidth()};
    const auto scintillatorLength{scintillator.PDRScintillatorLength()};
    const auto packageThickness{scintillator.PDRScintillatorPackageThickness()};
    const auto nSciPerLayer{scintillator.NScintillatorPerLayer()};

    const auto& meshScintillator{Mustard::Detector::CADMesh::TessellatedMesh::FromSTL(scintillator.STLFilePath())};
    const auto& meshSupport{Mustard::Detector::CADMesh::TessellatedMesh::FromSTL(support.STLFilePath())};

    const auto solidScintillator{meshScintillator->GetSolid()};
    const auto solidSupport{meshSupport->GetSolid()};
    const auto solidVirtualWallBox{Make<G4Box>("PDRVirtualWallBox",
                                               support.PDRSupportOuterWidth() / 2.,
                                               support.PDRSupportBaseWidth() / 2.,
                                               supportHeight / 2.)};
    const auto solidSiPMBox{Make<G4Box>("PDRSiPMBox",
                                        sipmWidth / 2.,
                                        sipmWidth / 2.,
                                        (sipmSensorThickness + sipmResinThickness + sipmCouplerThickness) / 2.)};
    const auto solidSiPMCoupler{Make<G4Box>("PDRSiPMCoupler", sipmWidth / 2., sipmWidth / 2., sipmCouplerThickness / 2.)};
    const auto solidSiPMSensor{Make<G4Box>("PDRSiPMSensor", sipmSensorWidth / 2., sipmSensorWidth / 2., sipmSensorThickness / 2.)};

    const auto logicScintillator{Make<G4LogicalVolume>(solidScintillator, fPlasticScintillator, scintillator.Name())};
    const auto logicSupport{Make<G4LogicalVolume>(solidSupport, fSteel, support.Name())};
    const auto logicVirtualWallBox{Make<G4LogicalVolume>(solidVirtualWallBox, fAir, "PDRVirtualWallBox")};
    const auto logicSiPMBox{Make<G4LogicalVolume>(solidSiPMBox, fEpoxy, "PDRSiPMBox")};
    const auto logicSiPMSensor{Make<G4LogicalVolume>(solidSiPMSensor, fSi, "PDRSiPMSensor")};
    const auto logicSiPMCoupler{Make<G4LogicalVolume>(solidSiPMCoupler, fSiliconeGrease, "PDRSiPMCoupler")};

    // clang-foramt off
    // #virtual box & inner facing direction
    //         1
    //         |
    //         v
    // 2 --> target <-- 4
    //         ^
    //         |
    //         3
    // y
    // ^
    // |
    // --->x
    // clang-format on
    const auto outerSciPosY{supportThickness / 2. + packageThickness + scintillatorThickness / 2.};
    const auto outerSciPosZ{0.};
    const auto innerSciPosX{0.};
    const auto innerSciPosY{-outerSciPosY};
    const auto distanceWallToTarget{support.PDRSupportOuterWidth() / 2. + support.PDRSupportSpacing() + support.PDRSupportBaseWidth() / 2.};
    const auto distanceSiPMToSci{(scintillatorLength + sipmCouplerThickness + sipmResinThickness + sipmSensorThickness) / 2.};

    for (int indexWall{}; indexWall < nSupport; ++indexWall) {
        auto position{G4ThreeVector(0., distanceWallToTarget, supportHeight / 2.).rotateZ(indexWall * 2 * pi / nSupport)};
        auto rotation{CLHEP::HepRotationZ(indexWall * 2 * pi / nSupport)};
        auto transform{G4Transform3D(rotation, position)};
        Make<G4PVPlacement>(transform,
                            logicVirtualWallBox,
                            "PDRVirtualWallBox",
                            Mother().LogicalVolume(),
                            false,
                            indexWall,
                            checkOverlaps);
    }

    for (int indexSci{}; indexSci < nSciPerLayer; ++indexSci) {
        // clang-format off
        auto innerSciPosZ{-(nSciPerLayer - 1) * packageThickness - nSciPerLayer / 2. * scintillatorWidth 
                                  + indexSci * (scintillatorWidth + packageThickness * 2)};
        // clang-format on
        auto innerSciPos{G4ThreeVector(innerSciPosX, innerSciPosY, innerSciPosZ)};
        auto innerSciTransform{G4Transform3D(CLHEP::HepRotation::IDENTITY, innerSciPos)};
        Make<G4PVPlacement>(innerSciTransform,
                            logicScintillator,
                            "PDRScintillator",
                            logicVirtualWallBox,
                            false,
                            indexSci,
                            checkOverlaps);
        for (int indexSiPM{}; indexSiPM < 2; ++indexSiPM) {
            auto innerSiPMPosX{distanceSiPMToSci * muc::pow(-1, indexSiPM)};
            auto innerSiPMRotYAngle{pi / 2. * muc::pow(-1, indexSiPM)};
            auto innerSiPMPos{G4ThreeVector(innerSiPMPosX, innerSciPosY, innerSciPosZ)};
            auto innerSiPMTransform{G4Transform3D(CLHEP::HepRotationY(innerSiPMRotYAngle), innerSiPMPos)};
            Make<G4PVPlacement>(innerSiPMTransform,
                                logicSiPMBox,
                                "PDRInnerSiPMBox",
                                logicVirtualWallBox,
                                false,
                                2 * indexSci + indexSiPM,
                                checkOverlaps);
        }

        auto outerSciPosX{innerSciPosZ};
        auto outerSciPos{G4ThreeVector(outerSciPosX, outerSciPosY, outerSciPosZ)};
        auto sciOuterTransform{G4Transform3D(CLHEP::HepRotationY(pi / 2.), outerSciPos)};
        Make<G4PVPlacement>(sciOuterTransform,
                            logicScintillator,
                            "PDRScintillator",
                            logicVirtualWallBox,
                            false,
                            nSciPerLayer + indexSci,
                            checkOverlaps);
        for (int indexSiPM{}; indexSiPM < 2; ++indexSiPM) {
            auto outerSiPMPosZ{distanceSiPMToSci * muc::pow(-1, indexSiPM)};
            auto outerSiPMRotYAngle{pi * indexSiPM};
            auto outerSiPMPos{G4ThreeVector(outerSciPosX, outerSciPosY, outerSiPMPosZ)};
            auto outerSiPMTransform{G4Transform3D(CLHEP::HepRotationY(outerSiPMRotYAngle), outerSiPMPos)};
            Make<G4PVPlacement>(outerSiPMTransform,
                                logicSiPMBox,
                                "PDRInnerSiPMBox",
                                logicVirtualWallBox,
                                false,
                                2 * (indexSci + nSciPerLayer) + indexSiPM,
                                checkOverlaps);
        }
    }
    Make<G4PVPlacement>(G4Transform3D::Identity,
                        logicSupport,
                        "PDRSupport",
                        logicVirtualWallBox,
                        false,
                        checkOverlaps);
    Make<G4PVPlacement>(G4Translate3D(0, 0, (sipmResinThickness + sipmSensorThickness) / 2.),
                        logicSiPMCoupler,
                        "PDRSiPMCoupler",
                        logicSiPMBox,
                        false,
                        checkOverlaps);
    Make<G4PVPlacement>(G4Translate3D(0, 0, -(sipmResinThickness + sipmCouplerThickness) / 2.),
                        logicSiPMSensor,
                        "PDRSiPMSensor",
                        logicSiPMBox,
                        false,
                        checkOverlaps);
}

} // namespace CRMuSR2::Detector::Definition
