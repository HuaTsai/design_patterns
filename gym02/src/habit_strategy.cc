#include "habit_strategy.hpp"

#include <algorithm>

namespace {
int CountIntersections(const std::vector<std::string> &a, const std::vector<std::string> &b) {
  std::vector<std::string> intersection;
  std::ranges::set_intersection(a, b, std::back_inserter(intersection));
  return static_cast<int>(intersection.size());
}
}  // namespace

std::shared_ptr<const Individual> HabitStrategy::MatchStrategy(
    std::shared_ptr<const Individual> individual) {
  // XXX: no other people to match, may have better position to guard
  if (individuals().size() <= 1) {
    return nullptr;
  }

  int best_intersecions =
      reverse() ? std::numeric_limits<int>::max() : std::numeric_limits<int>::min();
  for (const auto &p : individuals()) {
    if (p == individual) {
      continue;
    }
    const int intersections = CountIntersections(individual->habits(), p->habits());
    if (reverse()) {
      best_intersecions = std::min(intersections, best_intersecions);
    } else {
      best_intersecions = std::max(intersections, best_intersecions);
    }
  }

  std::vector<std::shared_ptr<Individual>> best_people;
  for (const auto &p : individuals()) {
    if (p == individual) {
      continue;
    }
    const int intersections = CountIntersections(individual->habits(), p->habits());
    if (intersections == best_intersecions) {
      best_people.push_back(p);
    }
  }

  if (best_people.empty()) {
    throw std::runtime_error("No match found");  // should not happen
  }

  auto engine = rng();
  return best_people[std::uniform_int_distribution<int>(
      0, static_cast<int>(best_people.size()) - 1)(engine)];
}
