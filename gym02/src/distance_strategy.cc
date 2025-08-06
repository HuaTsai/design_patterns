#include "distance_strategy.hpp"

namespace {
int DistanceSquared(const Coord &a, const Coord &b) {
  return ((a.x - b.x) * (a.x - b.x)) + ((a.y - b.y) * (a.y - b.y));
}
}  // namespace

std::shared_ptr<const Individual> DistanceStrategy::MatchStrategy(
    std::shared_ptr<const Individual> individual) {
  // XXX: no other people to match, may have better position to guard
  if (individuals().size() <= 1) {
    return nullptr;
  }

  int best_dist = reverse() ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max();
  for (const auto &p : individuals()) {
    if (p == individual) {
      continue;
    }
    auto d2 = DistanceSquared(individual->coord(), p->coord());
    best_dist = reverse() ? std::max(d2, best_dist) : std::min(d2, best_dist);
  }

  std::vector<std::shared_ptr<Individual>> best_people;
  for (const auto &p : individuals()) {
    if (p == individual) {
      continue;
    }
    if (DistanceSquared(individual->coord(), p->coord()) == best_dist) {
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
