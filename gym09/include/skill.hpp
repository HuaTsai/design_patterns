#pragma once

#include <memory>
#include <vector>

#define DECLARE_SKILL_SUBCLASS(name_en, name_zh, mp, parent)                                      \
  class name_en##Skill : public parent {                                                          \
    constexpr static int kMPCost = mp;                                                            \
                                                                                                  \
   public:                                                                                        \
    static std::string name() { return name_zh; }                                                 \
                                                                                                  \
    explicit name_en##Skill(const std::shared_ptr<Role> &role) : parent(name(), kMPCost, role) {} \
    void PerformSkill() override;                                                                 \
  };

class Role;

class Skill {
 public:
  static std::shared_ptr<Skill> Create(const std::string &name, std::shared_ptr<Role> role);

  explicit Skill(const std::string &name, int mp_cost, std::shared_ptr<Role> role)
      : name_(name), mp_cost_(mp_cost), role_(role) {}

  virtual ~Skill() = default;
  Skill(const Skill &) = delete;
  Skill &operator=(const Skill &) = delete;
  Skill(Skill &&) = delete;
  Skill &operator=(Skill &&) = delete;

  virtual void PerformSkill() = 0;

  [[nodiscard]] std::string name() const { return name_; }
  [[nodiscard]] int mp_cost() const { return mp_cost_; }
  [[nodiscard]] std::shared_ptr<Role> role() const { return role_.lock(); }

 private:
  std::string name_;
  int mp_cost_;
  std::weak_ptr<Role> role_;
};

class OneEnemySkill : public Skill {
 public:
  using Skill::Skill;
  std::vector<std::shared_ptr<Role>> RequestForTargets();
};

DECLARE_SKILL_SUBCLASS(Waterball, "水球", 50, OneEnemySkill)
DECLARE_SKILL_SUBCLASS(Fireball, "火球", 50, Skill)
DECLARE_SKILL_SUBCLASS(SelfHealing, "自我治療", 50, Skill)
DECLARE_SKILL_SUBCLASS(Petrochemical, "石化", 100, OneEnemySkill)
DECLARE_SKILL_SUBCLASS(Poison, "下毒", 80, OneEnemySkill)
DECLARE_SKILL_SUBCLASS(Summon, "召喚", 150, Skill)
DECLARE_SKILL_SUBCLASS(SelfExplosion, "自爆", 200, Skill)
DECLARE_SKILL_SUBCLASS(Cheerup, "鼓舞", 100, Skill)
DECLARE_SKILL_SUBCLASS(Curse, "詛咒", 100, OneEnemySkill)
DECLARE_SKILL_SUBCLASS(OnePunch, "一拳攻擊", 180, OneEnemySkill)
