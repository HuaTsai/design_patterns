#pragma once

#include <troop.hpp>

class RPG {
 public:
  RPG();
  void Initialize();
  [[nodiscard]] bool IsGameOver() const;
  void Battle();
  void ShowWinner();

 private:
  bool is_game_over_;
  std::shared_ptr<Troop> troop1_;
  std::shared_ptr<Troop> troop2_;
  std::shared_ptr<Role> hero_;
};
