#pragma once

#include <exporter/exporter.hpp>
#include <fstream>

class FileExporter : public Exporter {
 public:
  explicit FileExporter(const std::string &filename);

  ~FileExporter() override;
  FileExporter(const FileExporter &) = delete;
  FileExporter &operator=(const FileExporter &) = delete;
  FileExporter(FileExporter &&) = delete;
  FileExporter &operator=(FileExporter &&) = delete;

  void Export(const std::string &message) override;

 private:
  std::ofstream ofs_;
};
