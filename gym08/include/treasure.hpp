#pragma once

#include <functional>
#include <map>
#include <map_object.hpp>
#include <memory>
#include <random>

// clang-format off
#define DECLARE_TREASURE_CLASS(ClassName, Probability)           \
  class ClassName : public Treasure {                            \
   public:                                                       \
    explicit ClassName(int row, int col) : Treasure(row, col) {} \
    constexpr static float kProbability = Probability;           \
  };

#define CREATE_TREASURE_FUNCTOR_MAP(ClassName)                                 \
  {                                                                            \
    ClassName::kProbability,                                                   \
        [](int row, int col) { return std::make_shared<ClassName>(row, col); } \
  }
// clang-format on

class Treasure : public MapObject {
 public:
  Treasure(int row, int col) : MapObject("x", row, col) {}
  static std::shared_ptr<Treasure> CreateRandomTreasure(int row, int col);
};

DECLARE_TREASURE_CLASS(SuperStar, 0.1)
DECLARE_TREASURE_CLASS(Poison, 0.25)
DECLARE_TREASURE_CLASS(AcceleratingPotion, 0.2)
DECLARE_TREASURE_CLASS(HealingPotion, 0.15)
DECLARE_TREASURE_CLASS(DevilFruit, 0.1)
DECLARE_TREASURE_CLASS(KingsRock, 0.1)
DECLARE_TREASURE_CLASS(DokodemoDoor, 0.1)

inline std::shared_ptr<Treasure> CreateRandomTreasure(int row, int col) {
  static const std::multimap<float, std::function<std::shared_ptr<Treasure>(int, int)>>
      creation_map = {
          CREATE_TREASURE_FUNCTOR_MAP(SuperStar),
          CREATE_TREASURE_FUNCTOR_MAP(Poison),
          CREATE_TREASURE_FUNCTOR_MAP(AcceleratingPotion),
          CREATE_TREASURE_FUNCTOR_MAP(HealingPotion),
          CREATE_TREASURE_FUNCTOR_MAP(DevilFruit),
          CREATE_TREASURE_FUNCTOR_MAP(KingsRock),
          CREATE_TREASURE_FUNCTOR_MAP(DokodemoDoor),
      };

  static std::uniform_real_distribution<float> dis(0, 1);
  static std::default_random_engine dre(std::random_device{}());
  float num = dis(dre);
  for (const auto &[prob, func] : creation_map) {
    if (num < prob) {
      return func(row, col);
    }
    num -= prob;
  }
  return nullptr;
}
