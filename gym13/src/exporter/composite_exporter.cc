#include <exporter/composite_exporter.hpp>

void CompositeExporter::Export(const std::string &message) {
  for (const auto &exporter : exporters_) {
    exporter->Export(message);
  }
}

void CompositeExporter::AddExporter(std::shared_ptr<Exporter> exporter) {
  exporters_.emplace_back(exporter);
}
