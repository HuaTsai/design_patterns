#pragma once

#include <exporter/composite_exporter.hpp>
#include <exporter/console_exporter.hpp>
#include <exporter/file_exporter.hpp>
#include <nlohmann/json.hpp>

inline std::shared_ptr<Exporter> BuildExporterFromJson(std::shared_ptr<Exporter> default_exporter,
                                                       const nlohmann::json &j) {
  if (j["type"] == "console") {
    return std::make_shared<ConsoleExporter>();
  }

  if (j["type"] == "file") {
    return std::make_shared<FileExporter>(j["filename"]);
  }

  if (j["type"] == "composite") {
    auto ret = std::make_shared<CompositeExporter>();
    for (const auto &exporter : j["children"]) {
      auto child_exporter = BuildExporterFromJson(default_exporter, exporter);
      if (child_exporter) {
        ret->AddExporter(child_exporter);
      }
    }
    return ret;
  }

  return default_exporter;
}
