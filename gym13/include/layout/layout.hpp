#pragma once

#include <log_level.hpp>
#include <string>

class Layout {
 public:
  Layout() = default;
  virtual ~Layout() = default;
  Layout(const Layout &) = delete;
  Layout &operator=(const Layout &) = delete;
  Layout(Layout &&) = delete;
  Layout &operator=(Layout &&) = delete;

  virtual std::string Process(LogLevel level, const std::string &logger_name,
                              const std::string &message) = 0;
};
