#pragma once

#include <exporter/exporter.hpp>
#include <layout/layout.hpp>
#include <log_level.hpp>
#include <memory>
#include <nlohmann/json.hpp>
#include <unordered_map>

class Logger : public std::enable_shared_from_this<Logger> {
 public:
  // Root logger
  static std::shared_ptr<Logger> Create(LogLevel level, std::shared_ptr<Exporter> exporter,
                                        std::shared_ptr<Layout> layout);

  // Children loggers
  template <typename... Args>
  static std::shared_ptr<Logger> Create(const std::string &name,
                                        std::shared_ptr<Logger> parent_logger, Args... args);

  static void InitLoggersFromJson(const std::string &filename);
  static void CreateChildrenLoggersFromJson(const std::string &name, std::shared_ptr<Logger> parent,
                                            nlohmann::json &j);
  static std::shared_ptr<Logger> GetLogger(const std::string &name);

  void Trace(const std::string &message);
  void Info(const std::string &message);
  void Debug(const std::string &message);
  void Warn(const std::string &message);
  void Error(const std::string &message);

  std::shared_ptr<Exporter> exporter() const { return exporter_; }
  std::shared_ptr<Layout> layout() const { return layout_; }
  Logger(LogLevel level, std::shared_ptr<Logger> parent_logger, const std::string &name,
         std::shared_ptr<Exporter> exporter, std::shared_ptr<Layout> layout);

 private:
  static std::unordered_map<std::string, std::shared_ptr<Logger>> &loggers();

  LogLevel level_;
  std::shared_ptr<Logger> parent_logger_;
  std::string name_;
  std::shared_ptr<Exporter> exporter_;
  std::shared_ptr<Layout> layout_;
};

namespace detail {
template <typename T, typename... Args>
T GetArgOrDefault(T default_value, Args... args) {
  T result = default_value;
  (..., ([&] {
     if constexpr (std::is_same_v<std::decay_t<Args>, T>) {
       result = args;
     }
   }()));
  return result;
}

template <typename T, typename... Args>
std::shared_ptr<T> GetSharedPtrOrDefault(std::shared_ptr<T> default_value, Args... args) {
  std::shared_ptr<T> result = default_value;
  (..., ([&] {
     if constexpr (std::is_convertible_v<std::decay_t<Args>, std::shared_ptr<T>>) {
       result = args;
     }
   }()));
  return result;
}
}  // namespace detail

template <typename... Args>
std::shared_ptr<Logger> Logger::Create(const std::string &name,
                                       std::shared_ptr<Logger> parent_logger, Args... args) {
  if (!parent_logger) {
    throw std::invalid_argument("Parent logger cannot be null");
  }

  if (loggers().contains(name)) {
    return Logger::loggers()[name];
  }

  auto level = detail::GetArgOrDefault(parent_logger->level_, args...);
  auto exporter = detail::GetSharedPtrOrDefault(parent_logger->exporter_, args...);
  auto layout = detail::GetSharedPtrOrDefault(parent_logger->layout_, args...);

  loggers()[name] = std::make_shared<Logger>(level, parent_logger, name, exporter, layout);
  return loggers()[name];
}
