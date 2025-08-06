#include "system.hpp"

#include <unordered_set>

System::System(const std::vector<std::shared_ptr<Individual>> &individuals,
               std::shared_ptr<Strategy> strategy)
    : individuals_(individuals), strategy_(strategy) {
  std::unordered_set<int> idset;
  for (auto &individual : individuals_) {
    if (idset.contains(individual->id())) {
      throw std::invalid_argument("Duplicate id");
    }
    idset.insert(individual->id());
  }
}

std::shared_ptr<const Individual> System::Match(std::shared_ptr<const Individual> individual) {
  return strategy_->MatchStrategy(individual);
}
