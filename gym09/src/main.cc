#include <rpg.hpp>

int main() {
  auto rpg = std::make_shared<RPG>();
  rpg->Initialize();
  while (!rpg->IsGameOver()) {
    rpg->Battle();
  }
  rpg->ShowWinner();
}
