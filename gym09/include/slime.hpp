#pragma once

#include <ai.hpp>

class Slime : public AI {
  constexpr static int kHp = 100;
  constexpr static int kMp = 0;
  constexpr static int kStr = 50;
  constexpr static int kHealSummonerHp = 30;

 public:
  explicit Slime(std::shared_ptr<Troop> troop, std::string name, std::shared_ptr<Role> summoner);
  void TakeDamage(int damage) override;

 private:
  std::shared_ptr<Role> summoner_;
};
