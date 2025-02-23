#include "game.hpp"

int main() {
  auto deck = std::make_shared<Deck>();
  auto game = std::make_shared<Game>(deck);
  game->Start();
}
