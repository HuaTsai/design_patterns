#pragma once

class Sprite {
 public:
  explicit Sprite(char entity);
  virtual ~Sprite() = default;
  char entity() const;

 private:
  char entity_;
};

class FireSprite : public Sprite {
  static constexpr char kEntity = 'F';

 public:
  FireSprite();
};

class WaterSprite : public Sprite {
  static constexpr char kEntity = 'W';

 public:
  WaterSprite();
};

class HeroSprite : public Sprite {
  static constexpr char kEntity = 'H';
  static constexpr int kHp = 30;

 public:
  HeroSprite();
  void Heal(int hp);
  void Damage(int hp);
  int hp() const;

 private:
  int hp_;
};
