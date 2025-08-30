#pragma once

#include <genetic_algorithm_solver/individual.hpp>

struct Population {
  std::vector<std::shared_ptr<Individual>> individuals;
  auto begin() { return individuals.begin(); }
  auto end() { return individuals.end(); }
  auto begin() const { return individuals.cbegin(); }
  auto end() const { return individuals.cend(); }
  size_t size() const { return individuals.size(); }
};