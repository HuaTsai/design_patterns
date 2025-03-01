#pragma once

#include <role.hpp>

class Troop {
 public:
  [[nodiscard]] bool IsAnnihilated() const;
  void AddRole(std::shared_ptr<Role> role);
  [[nodiscard]] std::vector<std::shared_ptr<Role>> GetAllies() const;
  [[nodiscard]] std::vector<std::shared_ptr<Role>> GetAliveAllies() const;
  [[nodiscard]] std::vector<std::shared_ptr<Role>> GetEnemies() const;
  [[nodiscard]] std::vector<std::shared_ptr<Role>> GetAliveEnemies() const;

  void set_enemy_troop(std::shared_ptr<Troop> troop);

 private:
  std::vector<std::shared_ptr<Role>> roles_;
  std::weak_ptr<Troop> enemy_troop_;
};
