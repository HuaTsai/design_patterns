#pragma once

#include <layout/layout.hpp>

class StandardLayout : public Layout {
 public:
  using Layout::Layout;
  std::string Process(LogLevel level, const std::string &logger_name,
                      const std::string &message) override;
};
