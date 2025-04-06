#include <exporter/builder.hpp>
#include <fstream>
#include <layout/builder.hpp>
#include <logger.hpp>
#include <print>

std::shared_ptr<Logger> Logger::Create(LogLevel level, std::shared_ptr<Exporter> exporter,
                                       std::shared_ptr<Layout> layout) {
  loggers()["root"] = std::make_shared<Logger>(level, nullptr, "root", exporter, layout);
  return loggers()["root"];
}

void Logger::InitLoggersFromJson(const std::string &filename) {
  std::ifstream ifs(filename);
  if (!ifs) {
    std::print("Could not open file: {}\n", filename);
    return;
  }

  nlohmann::json j;
  ifs >> j;
  ifs.close();

  auto loggers = j["loggers"];

  // Root logger
  auto root_level = StringToLogLevel(loggers["level"]);
  auto root_exporter = BuildExporterFromJson(nullptr, loggers["exporter"]);
  auto root_layout = BuildLayoutFromJson(nullptr, loggers["layout"]);
  auto root_logger =
      std::make_shared<Logger>(root_level, nullptr, "root", root_exporter, root_layout);

  // Children of root logger
  for (auto it = loggers.begin(); it != loggers.end(); ++it) {
    if (it.key() == "level" || it.key() == "exporter" || it.key() == "layout") {
      continue;
    }
    CreateChildrenLoggersFromJson(it.key(), root_logger, *it);
  }
}

void Logger::CreateChildrenLoggersFromJson(const std::string &name, std::shared_ptr<Logger> parent,
                                           nlohmann::json &j) {
  // clang-format off
  auto level = j.contains("level") ? StringToLogLevel(j["level"]) : parent->level_;
  auto exporter = j.contains("exporter") ? BuildExporterFromJson(parent->exporter_, j["exporter"]) : parent->exporter_;
  auto layout = j.contains("layout") ? BuildLayoutFromJson(parent->layout_, j["layout"]) : parent->layout_;
  // clang-format on

  auto logger = Logger::Create(name, parent, level, exporter, layout);
  for (auto it = j.begin(); it != j.end(); ++it) {
    if (it.key() == "level" || it.key() == "exporter" || it.key() == "layout") {
      continue;
    }
    CreateChildrenLoggersFromJson(it.key(), logger, *it);
  }
}

std::shared_ptr<Logger> Logger::GetLogger(const std::string &name) {
  if (loggers().contains(name)) {
    return loggers()[name];
  }
  std::print("Logger with name {} does not exist\n", name);
  return nullptr;
}

Logger::Logger(LogLevel level, std::shared_ptr<Logger> parent_logger, const std::string &name,
               std::shared_ptr<Exporter> exporter, std::shared_ptr<Layout> layout)
    : level_(level),
      parent_logger_(parent_logger),
      name_(name),
      exporter_(exporter),
      layout_(layout) {}

void Logger::Trace(const std::string &message) {
  if (level_ > LogLevel::kTrace) {
    return;
  }
  auto formatted_message = layout_->Process(LogLevel::kTrace, name_, message);
  exporter_->Export(formatted_message);
}

void Logger::Info(const std::string &message) {
  if (level_ > LogLevel::kInfo) {
    return;
  }
  auto formatted_message = layout_->Process(LogLevel::kInfo, name_, message);
  exporter_->Export(formatted_message);
}

void Logger::Debug(const std::string &message) {
  if (level_ > LogLevel::kDebug) {
    return;
  }
  auto formatted_message = layout_->Process(LogLevel::kDebug, name_, message);
  exporter_->Export(formatted_message);
}

void Logger::Warn(const std::string &message) {
  if (level_ > LogLevel::kWarn) {
    return;
  }
  auto formatted_message = layout_->Process(LogLevel::kWarn, name_, message);
  exporter_->Export(formatted_message);
}

void Logger::Error(const std::string &message) {
  if (level_ > LogLevel::kError) {
    return;
  }
  auto formatted_message = layout_->Process(LogLevel::kError, name_, message);
  exporter_->Export(formatted_message);
}

std::unordered_map<std::string, std::shared_ptr<Logger>> &Logger::loggers() {
  static std::unordered_map<std::string, std::shared_ptr<Logger>> loggers;
  return loggers;
}
