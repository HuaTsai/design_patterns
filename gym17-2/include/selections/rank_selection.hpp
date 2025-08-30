#pragma once

#include <algorithm>
#include <genetic_algorithm_solver/selection.hpp>
#include <numeric>
#include <random>

class RankSelection : public Selection {
 public:
  using Selection::Selection;

  std::shared_ptr<Population> operator()(
      const std::shared_ptr<Population> &population) const override {
    const double sp = 1.5;  // selection pressure
    int n = population->size();
    std::vector<double> probs(n);
    for (int i = 0; i < n; ++i) {
      probs[i] = 1. / n * (sp - (2 * sp - 2) * i / (n - 1));
    }
    std::vector<double> cumulative_probs(n);
    std::partial_sum(probs.begin(), probs.end(), cumulative_probs.begin());

    auto sorted_population = std::make_shared<Population>();
    for (const auto &individual : population->individuals) {
      auto copy = factory()->CreateCopiedIndividual(individual);
      sorted_population->individuals.emplace_back(copy);
    }
    std::ranges::sort(sorted_population->individuals, [](const std::shared_ptr<Individual> &a,
                                                         const std::shared_ptr<Individual> &b) {
      return a->Fitness() > b->Fitness();
    });

    static std::mt19937 gen(std::random_device{}());
    std::uniform_real_distribution<> dis(0, cumulative_probs.back());

    auto selected = std::make_shared<Population>();
    for (int i = 0; i < n; ++i) {
      auto it = std::ranges::lower_bound(cumulative_probs, dis(gen));
      int index = std::distance(cumulative_probs.begin(), it);
      selected->individuals.emplace_back(sorted_population->individuals[index]);
    }
    return selected;
  }
};