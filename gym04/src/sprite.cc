#include "sprite.hpp"

Sprite::Sprite(char entity) : entity_(entity) {}

char Sprite::entity() const { return entity_; }

FireSprite::FireSprite() : Sprite(kEntity) {}

WaterSprite::WaterSprite() : Sprite(kEntity) {}

HeroSprite::HeroSprite() : Sprite(kEntity), hp_(kHp) {}

void HeroSprite::Heal(int hp) { hp_ += hp; }

void HeroSprite::Damage(int hp) { hp_ -= hp; }

int HeroSprite::hp() const { return hp_; }
