#include <iostream>

#include "world.hpp"

int main() {
  World world;

  std::cout << "Initial world:\n";
  world.Draw();

  std::string instruct = "Move command \"x1 x2\" or EOF (^D)? ";
  std::cout << instruct;
  int x1, x2;
  while (std::cin >> x1 >> x2) {
    world.Move(x1, x2);
    world.Draw();
    std::cout << instruct;
  }

  std::cout << "\nBye!\n";
}
