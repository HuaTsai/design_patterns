#pragma once

#include <algorithm>
#include <genetic_algorithm_solver/selection.hpp>
#include <random>
#include <utility>

class TournamentSelection : public Selection {
 public:
  using Selection::Selection;

  std::shared_ptr<Population> operator()(
      const std::shared_ptr<Population> &population) const override {
    const int n = population->size();
    const int k = n / 2;  // tournament size
    std::vector<int> indices(n);
    std::iota(indices.begin(), indices.end(), 0);
    static std::mt19937 gen(std::random_device{}());
    auto ret = std::make_shared<Population>();
    while (std::cmp_less(ret->size(), n)) {
      std::shuffle(indices.begin(), indices.end(), gen);
      auto group = std::make_shared<Population>();
      for (int i = 0; i < k; ++i) {
        auto copy = factory()->CreateCopiedIndividual(population->individuals[indices[i]]);
        group->individuals.emplace_back(copy);
      }

      auto it = std::ranges::max_element(
          group->individuals,
          [](const std::shared_ptr<Individual> &a, const std::shared_ptr<Individual> &b) {
            return a->Fitness() < b->Fitness();
          });
      ret->individuals.emplace_back(*it);
    }
    return ret;
  }
};