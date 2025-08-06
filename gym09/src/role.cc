#include <print>
#include <role.hpp>
#include <troop.hpp>

Role::Role(std::shared_ptr<Troop> troop, const std::string &name, int hp, int mp, int str)
    : troop_(troop), name_(name), hp_(hp), mp_(mp), str_(str) {}

void Role::AddSkill(const std::string &name) {
  skills_.emplace_back(Skill::Create(name, shared_from_this()));
}

void Role::Heal(int hp) { hp_ += hp; }

void Role::Attack(std::shared_ptr<Role> target, int hp) { state_->Attack(target, hp); }

void Role::TakeDamage(int damage) {
  hp_ -= damage;
  if (hp_ <= 0) {
    std::println("{} 死亡。", name_);
    for (const auto &curser : cursers_) {
      if (auto curser_ptr = curser.lock(); curser_ptr->IsAlive()) {
        curser_ptr->Heal(mp_);
      }
    }
  }
}

void Role::Action() {
  state_->Action();
  if (state_->next_state()) {
    SetState(state_->next_state());
  }
}

void Role::ActionStartEvent() { state_->ActionStartEvent(); }

void Role::ActionEndEvent() { state_->ActionEndEvent(); }

void Role::BasicAttack(std::shared_ptr<Role> target) {
  std::println("{} 攻擊 {}。", name_, target->name());
  Attack(target, str_);
}

void Role::SetState(std::shared_ptr<State> state) { state_ = state; }

void Role::AddCurser(std::shared_ptr<Role> curser) {
  auto it = std::ranges::find_if(cursers_, [curser](auto c) { return c.lock() == curser; });
  if (it == cursers_.end()) {
    cursers_.emplace_back(curser);
  }
}

bool Role::IsAlive() const { return hp_ > 0; }

bool Role::IsDead() const { return hp_ <= 0; }

void Role::ConsumeMp(int mp) { mp_ -= mp; }

std::string Role::StateName() const { return state_->name(); }

std::shared_ptr<Troop> Role::troop() const { return troop_.lock(); }

std::string Role::name() const { return name_; }

int Role::hp() const { return hp_; }

int Role::mp() const { return mp_; }

int Role::str() const { return str_; }

std::shared_ptr<State> Role::state() const { return state_; }

std::vector<std::shared_ptr<Skill>> Role::skills() const { return skills_; }
