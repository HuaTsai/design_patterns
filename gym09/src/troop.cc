#include <algorithm>
#include <troop.hpp>

bool Troop::IsAnnihilated() const {
  return std::ranges::all_of(roles_, [](auto role) { return role->IsDead(); });
}

void Troop::AddRole(std::shared_ptr<Role> role) { roles_.emplace_back(role); }

std::vector<std::shared_ptr<Role>> Troop::GetAllies() const { return roles_; }

std::vector<std::shared_ptr<Role>> Troop::GetAliveAllies() const {
  std::vector<std::shared_ptr<Role>> ret;
  for (const auto &role : roles_) {
    if (role->IsAlive()) {
      ret.emplace_back(role);
    }
  }
  return ret;
}

std::vector<std::shared_ptr<Role>> Troop::GetEnemies() const {
  return enemy_troop_.lock()->GetAllies();
}

std::vector<std::shared_ptr<Role>> Troop::GetAliveEnemies() const {
  return enemy_troop_.lock()->GetAliveAllies();
}

void Troop::set_enemy_troop(std::shared_ptr<Troop> troop) { enemy_troop_ = troop; }
