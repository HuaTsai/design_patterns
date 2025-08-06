#include <iostream>
#include <print>

#include "world.hpp"

int main() {
  World world;

  std::print("Initial world:\n");
  world.Draw();

  const std::string instruct = "Move command \"x1 x2\" or EOF (^D)? ";
  std::print("{}", instruct);
  int x1 = 0;
  int x2 = 0;
  while (std::cin >> x1 >> x2) {
    world.Move(x1, x2);
    world.Draw();
    std::print("{}", instruct);
  }

  std::print("\nBye!\n");
}
