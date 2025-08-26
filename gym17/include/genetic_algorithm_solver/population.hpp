#pragma once

#include <vector>

template <typename GeneType>
struct Individual {
  std::vector<GeneType> genes;
};

template <typename GeneType>
struct Population {
  std::vector<Individual<GeneType>> individuals;
  auto begin() { return individuals.begin(); }
  auto end() { return individuals.end(); }
  auto begin() const { return individuals.cbegin(); }
  auto end() const { return individuals.cend(); }
  size_t size() const { return individuals.size(); }
};