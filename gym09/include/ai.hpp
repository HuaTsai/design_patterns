#pragma once

#include <role.hpp>

class AI : public Role {
 public:
  explicit AI(std::shared_ptr<Troop> troop, std::string name, int hp, int mp, int str);
  std::shared_ptr<Skill> S1Input() override;
  std::shared_ptr<Role> S2Input(const std::vector<std::shared_ptr<Role>> &candidates) override;
  std::vector<std::shared_ptr<Role>> S2InputMultiple(
      const std::vector<std::shared_ptr<Role>> &candidates, int slots) override;

 private:
  int seed_;
};
