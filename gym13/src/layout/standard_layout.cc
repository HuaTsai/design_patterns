#include <chrono>
#include <format>
#include <layout/standard_layout.hpp>

std::string StandardLayout::Process(LogLevel level, const std::string &logger_name,
                                    const std::string &message) {
  auto now_ms = std::chrono::floor<std::chrono::milliseconds>(std::chrono::system_clock::now());
  return std::format("{:%Y-%m-%d %H:%M:%S} | -{} {} {}", now_ms, LogLevelToString(level),
                     logger_name, message);
}
