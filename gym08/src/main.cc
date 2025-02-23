#include <game.hpp>
#include <memory>
#include <treasure.hpp>

int main() {
  auto game = std::make_unique<Game>();
  game->Start();
  while (!game->IsFinish()) {
    game->RoundStart();
  }
  game->Finish();
}
