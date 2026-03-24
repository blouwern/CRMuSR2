#pragma once

#include "Mustard/Detector/Description/DescriptionBase.h++"

#include "envparse/parse.h++"
#include <filesystem>
#include <string>

namespace CRMuSR2::Detector::Description {

class GeometryReference final
    : public Mustard::Detector::Description::DescriptionBase<
          GeometryReference> {
  friend Mustard::Env::Memory::SingletonInstantiator;

private:
  GeometryReference();
  ~GeometryReference() override = default;

public:
  auto STLFileDirPath() const -> const auto & { return fSTLFileDirPath; }
  auto ParsedSTLFileDirPath() const -> std::filesystem::path { return envparse::parse(fSTLFileDirPath); }

  auto STLFileDirPath(std::string val) -> void { fSTLFileDirPath = std::move(val); }

private:
  auto ImportAllValue(const YAML::Node &node) -> void override;
  auto ExportAllValue(YAML::Node &node) const -> void override;

private:
  std::string fSTLFileDirPath;
};

} // namespace CRMuSR2::Detector::Description
