#include <exporter/console_exporter.hpp>
#include <print>

void ConsoleExporter::Export(const std::string &message) { std::print("{}\n", message); }
