#include <slime.hpp>

Slime::Slime(std::shared_ptr<Troop> troop, std::string name, std::shared_ptr<Role> summoner)
    : AI(troop, name, kHp, kMp, kStr), summoner_(summoner) {}

void Slime::TakeDamage(int damage) {
  AI::TakeDamage(damage);
  if (IsDead() && summoner_->IsAlive()) {
    summoner_->Heal(kHealSummonerHp);
  }
}
