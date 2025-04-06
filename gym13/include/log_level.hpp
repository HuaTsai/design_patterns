#pragma once

#include <stdexcept>
#include <string>

enum class LogLevel { kTrace = 1, kInfo = 2, kDebug = 3, kWarn = 4, kError = 5 };

inline std::string LogLevelToString(LogLevel level) {
  switch (level) {
    case LogLevel::kTrace:
      return "TRACE";
    case LogLevel::kInfo:
      return "INFO";
    case LogLevel::kDebug:
      return "DEBUG";
    case LogLevel::kWarn:
      return "WARN";
    case LogLevel::kError:
      return "ERROR";
    default:
      throw std::invalid_argument("Invalid log level");
  }
}

inline LogLevel StringToLogLevel(const std::string &level_str) {
  if (level_str == "TRACE") {
    return LogLevel::kTrace;
  }
  if (level_str == "INFO") {
    return LogLevel::kInfo;
  }
  if (level_str == "DEBUG") {
    return LogLevel::kDebug;
  }
  if (level_str == "WARN") {
    return LogLevel::kWarn;
  }
  if (level_str == "ERROR") {
    return LogLevel::kError;
  }
  throw std::invalid_argument("Invalid log level string");
}
