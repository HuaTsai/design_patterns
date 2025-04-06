#include <exporter/file_exporter.hpp>
#include <fstream>
#include <print>

FileExporter::FileExporter(const std::string &filename) { ofs_.open(filename, std::ios::app); }

FileExporter::~FileExporter() {
  if (ofs_.is_open()) {
    ofs_.close();
  }
}

void FileExporter::Export(const std::string &message) { std::print(ofs_, "{}\n", message); }
