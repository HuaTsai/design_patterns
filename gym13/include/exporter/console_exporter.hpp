#pragma once

#include <exporter/exporter.hpp>

class ConsoleExporter : public Exporter {
 public:
  using Exporter::Exporter;
  void Export(const std::string &message) override;
};
