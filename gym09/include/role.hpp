#pragma once

#include <skill.hpp>
#include <state.hpp>
#include <vector>

class Troop;

class Role : public std::enable_shared_from_this<Role> {
 public:
  explicit Role(std::shared_ptr<Troop> troop, std::string name, int hp, int mp, int str);

  virtual ~Role() = default;
  Role(const Role &) = delete;
  Role &operator=(const Role &) = delete;
  Role(Role &&) = delete;
  Role &operator=(Role &&) = delete;

  void AddSkill(const std::string &name);
  void Heal(int hp);
  void Attack(std::shared_ptr<Role> target, int hp);
  virtual void TakeDamage(int damage);
  void Action();
  void ActionStartEvent();
  void ActionEndEvent();
  virtual std::shared_ptr<Skill> S1Input() = 0;
  virtual std::shared_ptr<Role> S2Input(const std::vector<std::shared_ptr<Role>> &candidates) = 0;
  virtual std::vector<std::shared_ptr<Role>> S2InputMultiple(
      const std::vector<std::shared_ptr<Role>> &candidates, int slots) = 0;
  void BasicAttack(std::shared_ptr<Role> target);
  void SetState(std::shared_ptr<State> state);
  void AddCurser(std::shared_ptr<Role> curser);
  bool IsAlive() const;
  bool IsDead() const;
  void ConsumeMp(int mp);
  std::string StateName() const;

  std::shared_ptr<Troop> troop() const;
  std::string name() const;
  int hp() const;
  int mp() const;
  int str() const;
  std::shared_ptr<State> state() const;
  std::vector<std::shared_ptr<Skill>> skills() const;

 private:
  std::weak_ptr<Troop> troop_;
  std::string name_;
  int hp_;
  int mp_;
  int str_;
  std::vector<std::shared_ptr<Skill>> skills_;
  std::shared_ptr<State> state_;
  std::vector<std::weak_ptr<Role>> cursers_;
};
