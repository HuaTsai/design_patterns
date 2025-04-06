#pragma once

#include <string>

class Exporter {
 public:
  Exporter() = default;

  virtual ~Exporter() = default;
  Exporter(const Exporter &) = delete;
  Exporter &operator=(const Exporter &) = delete;
  Exporter(Exporter &&) = delete;
  Exporter &operator=(Exporter &&) = delete;

  virtual void Export(const std::string &message) = 0;
};
