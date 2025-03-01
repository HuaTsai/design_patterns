#pragma once

#include <role.hpp>

class Hero : public Role {
 public:
  using Role::Role;
  std::shared_ptr<Skill> S1Input() override;
  std::shared_ptr<Role> S2Input(const std::vector<std::shared_ptr<Role>> &candidates) override;
  std::vector<std::shared_ptr<Role>> S2InputMultiple(
      const std::vector<std::shared_ptr<Role>> &candidates, int slots) override;
};
