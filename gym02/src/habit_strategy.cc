#include "habit_strategy.hpp"

#include <algorithm>

namespace {
int CountIntersections(const std::vector<std::string> &a, const std::vector<std::string> &b) {
  std::vector<std::string> intersection;
  std::ranges::set_intersection(a, b, std::back_inserter(intersection));
  return intersection.size();
}
}  // namespace

std::shared_ptr<const Individual> HabitStrategy::MatchStrategy(
    std::shared_ptr<const Individual> individual) {
  // XXX: no other people to match, may have better position to guard
  if (individuals_.size() <= 1) {
    return nullptr;
  }

  int best_intersecions =
      reverse_ ? std::numeric_limits<int>::max() : std::numeric_limits<int>::min();
  for (auto p : individuals_) {
    if (p == individual) continue;  // skip self
    int intersections = CountIntersections(individual->habits(), p->habits());
    if (reverse_) {
      best_intersecions = std::min(intersections, best_intersecions);
    } else {
      best_intersecions = std::max(intersections, best_intersecions);
    }
  }

  std::vector<std::shared_ptr<Individual>> best_people;
  for (auto p : individuals_) {
    if (p == individual) continue;  // skip self
    int intersections = CountIntersections(individual->habits(), p->habits());
    if (intersections == best_intersecions) {
      best_people.push_back(p);
    }
  }

  if (best_people.size() == 0) {
    throw std::runtime_error("No match found");  // should not happen
  }

  return best_people[std::uniform_int_distribution<int>(
      0, static_cast<int>(best_people.size()) - 1)(rng_)];
}
