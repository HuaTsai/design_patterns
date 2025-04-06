#include <exporter/composite_exporter.hpp>
#include <exporter/console_exporter.hpp>
#include <exporter/file_exporter.hpp>
#include <layout/standard_layout.hpp>
#include <logger.hpp>

int main() {
  // Option 1: Initialize loggers manually
  auto root = Logger::Create(LogLevel::kDebug, std::make_shared<ConsoleExporter>(),
                             std::make_shared<StandardLayout>());

  // clang-format off
  auto game_logger = Logger::Create(
      "app.game", root, LogLevel::kInfo,
      std::make_shared<CompositeExporter>(
          std::make_shared<ConsoleExporter>(),
          std::make_shared<CompositeExporter>(
              std::make_shared<FileExporter>("game.log"),
              std::make_shared<FileExporter>("game.backup.log")
          )
      )
  );
  // clang-format on

  auto ai_logger = Logger::Create("app.game.ai", game_logger, LogLevel::kTrace,
                                  std::make_shared<StandardLayout>());

  // Option 2: Initialize loggers from JSON
  // Logger::InitLoggersFromJson("../data/config.json");

  auto MakeDecision = [](int ai_id) {
    auto log = Logger::GetLogger("app.game.ai");
    log->Trace(std::format("AI {} starts making decisions...", ai_id));
    log->Warn(std::format("AI {} decides to give up.", ai_id));
    log->Error("Something goes wrong when AI gives up.");
    log->Trace(std::format("AI {} completes its decision.", ai_id));
  };

  auto log = Logger::GetLogger("app.game");
  log->Info("The game begins.");
  for (int i = 1; i <= 4; ++i) {
    log->Trace(std::format("The player {} begins his turn.", i));
    MakeDecision(i);
    log->Trace(std::format("The player {} finishes his turn.", i));
  }
  log->Debug("Game ends.");
}
