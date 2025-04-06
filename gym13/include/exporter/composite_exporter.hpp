#pragma once

#include <exporter/exporter.hpp>
#include <memory>
#include <vector>

class CompositeExporter : public Exporter {
 public:
  template <typename... Exporters>
  explicit CompositeExporter(std::shared_ptr<Exporters>... exporters);

  void Export(const std::string &message) override;
  void AddExporter(std::shared_ptr<Exporter> exporter);

 private:
  std::vector<std::shared_ptr<Exporter>> exporters_;
};

template <typename... Exporters>
CompositeExporter::CompositeExporter(std::shared_ptr<Exporters>... exporters) {
  static_assert((std::is_base_of_v<Exporter, Exporters> && ...),
                "All arguments must be Exporter-derived");
  (exporters_.emplace_back(exporters), ...);
}
