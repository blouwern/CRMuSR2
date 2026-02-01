#include "CRMuSR2/Detector/Description/PDRScintillator.h++"
#include "CRMuSR2/Detector/Description/PDRSupport.h++"

#include "Mustard/Utility/LiteralUnit.h++"

namespace CRMuSR2::Detector::Description {

using namespace Mustard::LiteralUnit::Length;
using namespace Mustard::LiteralUnit::Energy;
using namespace Mustard::LiteralUnit::Time;

PDRScintillator::PDRScintillator() :
    DescriptionBase{"PDRScintillator"},
    fSTLFilePath{""},
    fNScintillatorPerLayer{16},
    fPDRScintillatorLength{65.5_cm},
    fPDRScintillatorThickness{2_cm},
    fPDRScintillatorWidth{4_cm},
    fPDRScintillatorHeadWidth{3_cm},
    fPDRScintillatorHeadHight{2_cm},
    fPDRScintillatorPackageThickness{0.05_cm},
    fPSScintillationEnergyBin{},
    fPSScintillationComponent1{},
    fPSScintillationYield{10000.},
    fPSScintillationTimeConstant1{2.1_ns},
    fPSResolutionScale{1.} {
    fPSScintillationEnergyBin = {2.482953109_eV, 2.489659196_eV, 2.496003695_eV, 2.502381059_eV, 2.508791544_eV, 2.515235634_eV, 2.521712914_eV, 2.528223186_eV, 2.53476796_eV, 2.541347168_eV, 2.548161747_eV,
                                 2.554661489_eV, 2.561202446_eV, 2.567815247_eV, 2.574829427_eV, 2.579956087_eV, 2.585046827_eV, 2.590273296_eV, 2.596648064_eV, 2.602100665_eV, 2.608203377_eV, 2.613926041_eV,
                                 2.61797784_eV, 2.622401485_eV, 2.628222987_eV, 2.632330767_eV, 2.637208697_eV, 2.643026898_eV, 2.647008211_eV, 2.651842137_eV, 2.658691238_eV, 2.665141972_eV, 2.671429914_eV,
                                 2.677283888_eV, 2.685400294_eV, 2.69325325_eV, 2.699300679_eV, 2.706719316_eV, 2.713494146_eV, 2.719892644_eV, 2.726076443_eV, 2.73102463_eV, 2.737402211_eV, 2.742231678_eV,
                                 2.748404443_eV, 2.754115306_eV, 2.759358856_eV, 2.764781943_eV, 2.76890398_eV, 2.776072945_eV, 2.782386965_eV, 2.789212011_eV, 2.795753365_eV, 2.802196767_eV, 2.806414568_eV,
                                 2.811221166_eV, 2.814980328_eV, 2.819868451_eV, 2.825619424_eV, 2.831284734_eV, 2.836501956_eV, 2.84333131_eV, 2.849700132_eV, 2.854645037_eV, 2.859428074_eV, 2.864396308_eV,
                                 2.869215654_eV, 2.876671121_eV, 2.883946516_eV, 2.890948342_eV, 2.897377698_eV, 2.904990895_eV, 2.914133981_eV, 2.923149418_eV, 2.93084661_eV, 2.93754637_eV, 2.942295531_eV,
                                 2.948393432_eV, 2.950505154_eV, 2.953888442_eV, 2.956461509_eV, 2.959992269_eV, 2.962296518_eV, 2.963894507_eV, 2.966508035_eV, 2.969782779_eV, 2.972055663_eV, 2.97447451_eV,
                                 2.976897154_eV, 2.979993842_eV, 2.982571392_eV, 2.984057776_eV, 2.986510592_eV, 2.989977852_eV, 2.992336239_eV, 2.994789689_eV, 2.997247019_eV, 2.999594545_eV, 3.002766198_eV,
                                 3.006660177_eV, 3.009685411_eV, 3.012724858_eV, 3.017190476_eV, 3.021169347_eV, 3.024479237_eV, 3.02868571_eV, 3.033628622_eV, 3.037260887_eV, 3.039760862_eV, 3.0437672_eV,
                                 3.049236157_eV, 3.054563595_eV, 3.059786635_eV, 3.065879764_eV, 3.072860517_eV, 3.083715748_eV, 3.098728373_eV, 3.111650017_eV};
    fPSScintillationComponent1 = {0.077888009, 0.082150664, 0.088739682, 0.095756293, 0.103193138, 0.111289285, 0.119298292, 0.126732782, 0.134934949, 0.143529913, 0.152476488, 0.16297777, 0.173540989, 0.186993338,
                                  0.200955848, 0.211164882, 0.222622367, 0.232494545, 0.244232765, 0.255609754, 0.2722475, 0.289500739, 0.300091751, 0.314133944, 0.331890226, 0.347596397, 0.365647018, 0.380866094,
                                  0.399555549, 0.412500396, 0.429919533, 0.45401665, 0.462738638, 0.476929472, 0.490301698, 0.497266344, 0.504161567, 0.515877668, 0.523951135, 0.535893102, 0.543232708, 0.557756994,
                                  0.566009808, 0.583304467, 0.594966465, 0.606232199, 0.620023278, 0.635371167, 0.647351693, 0.660163631, 0.679587504, 0.700735441, 0.721714308, 0.742391928, 0.760771645, 0.777741956,
                                  0.788358215, 0.804450384, 0.826447798, 0.843659688, 0.86502977, 0.884261775, 0.899289116, 0.916822104, 0.928268553, 0.938936237, 0.948338711, 0.961042779, 0.969245089, 0.982328519,
                                  0.995048127, 0.998512266, 1.0, 0.99249575, 0.981785089, 0.960954079, 0.931809338, 0.898882312, 0.87618235, 0.850207553, 0.821478459, 0.794677086, 0.772790048, 0.750823072, 0.725797968,
                                  0.6979187, 0.674004238, 0.65037776, 0.626744929, 0.595646008, 0.571557652, 0.552377475, 0.530034237, 0.504213142, 0.480734358, 0.458517559, 0.436292167, 0.413344652, 0.385161025,
                                  0.356410043, 0.337410262, 0.313685191, 0.286478918, 0.263165205, 0.240645736, 0.218947384, 0.198340354, 0.180335346, 0.165189116, 0.14669725, 0.121817485, 0.101515975, 0.079466925,
                                  0.056909146, 0.0343247, 0.016377592, 0.007494536, 0.00300246};
}

auto PDRScintillator::ImportAllValue(const YAML::Node& node) -> void {
    ImportValue(node, fSTLFilePath, "STLFilePath");
    ImportValue(node, fNScintillatorPerLayer, "NPDRScintillatorPerLayer");
    ImportValue(node, fPDRScintillatorLength, "PDRScintillatorLength");
    ImportValue(node, fPDRScintillatorThickness, "PDRScintillatorThickness");
    ImportValue(node, fPDRScintillatorWidth, "PDRScintillatorWidth");
    ImportValue(node, fPDRScintillatorHeadWidth, "PDRScintillatorHeadWidth");
    ImportValue(node, fPDRScintillatorHeadHight, "PDRScintillatorHeadHight");
    ImportValue(node, fPDRScintillatorPackageThickness, "PDRScintillatorPackageThickness");
}

auto PDRScintillator::ExportAllValue(YAML::Node& node) const -> void {
    ExportValue(node, fSTLFilePath, "STLFilePath");
    ExportValue(node, fNScintillatorPerLayer, "NPDRScintillatorPerLayer");
    ExportValue(node, fPDRScintillatorLength, "PDRScintillatorLength");
    ExportValue(node, fPDRScintillatorThickness, "PDRScintillatorThickness");
    ExportValue(node, fPDRScintillatorWidth, "PDRScintillatorWidth");
    ExportValue(node, fPDRScintillatorHeadWidth, "PDRScintillatorHeadWidth");
    ExportValue(node, fPDRScintillatorHeadHight, "PDRScintillatorHeadHight");
    ExportValue(node, fPDRScintillatorPackageThickness, "PDRScintillatorPackageThickness");
}

// auto PDRScintillator::CalculatePDRScintillatorInformation() const -> std::vector<PDRScintillatorInformation> {
//     auto support{PDRSupport::Instance()};
//     auto supportThickness{support.PDRSupportThickness()};
//     auto thicknessDirectionOffset{supportThickness / 2 + fPDRScintillatorPackageThickness + fPDRScintillatorThickness / 2};

// }

} // namespace CRMuSR2::Detector::Description
