#include <iostream>
#include <memory>
#include <print>

#include "distance_strategy.hpp"
#include "habit_strategy.hpp"
#include "system.hpp"

int main() {
  // erroneous input
  // auto e0 = std::make_shared<Individual>(0, Gender::kMale, 20, "Hi, I am p1",
  // "Basketball", Coord{1, 2}); auto e1 = std::make_shared<Individual>(1,
  // Gender::kMale, 12, "Hi, I am p1", "Basketball", Coord{1, 2}); auto e2 =
  // std::make_shared<Individual>(1, Gender::kMale, 20, std::string(201, ' '),
  // "Basketball", Coord{1, 2});

  auto p1 =
      std::make_shared<Individual>(1, Gender::kMale, 20, "Hi, I am p1", "Basketball", Coord{1, 2});
  std::print("Create p1:\n{}\n", *p1);

  auto p2 =
      std::make_shared<Individual>(2, Gender::kFemale, 22, "Hi, I am p2", "Swimming", Coord{3, 4});
  std::print("Create p2:\n{}\n", *p2);

  auto p3 = std::make_shared<Individual>(3, Gender::kFemale, 24, "Hi, I am p3",
                                         "Basketball,Swimming", Coord{5, 6});
  std::print("Create p3:\n{}\n", *p3);

  auto p4 = std::make_shared<Individual>(4, Gender::kMale, 26, "Hi, I am p4", "", Coord{7, 8});
  std::print("Create p4:\n{}\n", *p4);

  // duplicate id
  // auto p0 = std::make_shared<Individual>(1, Gender::kMale, 20, "Hi, I am p0",
  // "Basketball", Coord{1, 2}); std::vector<std::shared_ptr<Individual>>
  // individuals{p0, p1, p2, p3, p4};
  const std::vector<std::shared_ptr<Individual>> individuals{p1, p2, p3, p4};

  // auto strategy = std::shared_ptr<Strategy>(new HabitStrategy(individuals));
  auto strategy = std::shared_ptr<Strategy>(new DistanceStrategy(individuals));

  const auto &s = *strategy;  // avoid clang warning
  if (typeid(s) == typeid(HabitStrategy)) {
    std::print("Use habitStrategy\n");
  } else if (typeid(s) == typeid(DistanceStrategy)) {
    std::print("Use distance strategy\n");
  } else {
    throw std::runtime_error("Unknown strategy");
  }

  strategy->Reverse();
  std::print("Reverse strategy\n");

  auto system = std::make_shared<System>(individuals, strategy);

  std::print("\nSystem start... perform match\n");
  for (const auto &individual : individuals) {
    auto match = system->Match(individual);
    std::print("Match id {} -> id {}\n", individual->id(), match->id());
  }
}
