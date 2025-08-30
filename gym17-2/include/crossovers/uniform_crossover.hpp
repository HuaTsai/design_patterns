#pragma once

#include <algorithm>
#include <genetic_algorithm_solver/crossover.hpp>
#include <numeric>
#include <random>

class UniformCrossover : public Crossover {
 public:
  using Crossover::Crossover;

  std::shared_ptr<Population> operator()(
      const std::shared_ptr<Population> &parents) const override {
    int n = parents->size();
    int n_genes = parents->individuals[0]->size();
    static std::mt19937 gen(std::random_device{}());
    std::bernoulli_distribution dis(0.5);
    std::vector<int> indices(n);
    std::ranges::iota(indices, 0);
    std::ranges::shuffle(indices, gen);

    auto ret = std::make_shared<Population>();
    for (int i = 0; i < n; i += 2) {
      if (i + 1 == n) {
        auto copy = factory()->CreateCopiedIndividual(parents->individuals[indices[i]]);
        ret->individuals.emplace_back(copy);
        break;
      }

      int retry = 0;
      while (true) {
        auto offspring1 = factory()->CreateCopiedIndividual(parents->individuals[indices[i]]);
        auto offspring2 = factory()->CreateCopiedIndividual(parents->individuals[indices[i + 1]]);
        for (int j = 0; j < n_genes; ++j) {
          if (dis(gen)) {
            std::swap(offspring1->genes()[j], offspring2->genes()[j]);
          }
        }

        if (offspring1->IsValid() && offspring2->IsValid()) {
          ret->individuals.emplace_back(offspring1);
          ret->individuals.emplace_back(offspring2);
          break;
        }

        if (++retry == 100) {
          auto copy1 = factory()->CreateCopiedIndividual(parents->individuals[indices[i]]);
          auto copy2 = factory()->CreateCopiedIndividual(parents->individuals[indices[i + 1]]);
          ret->individuals.emplace_back(copy1);
          ret->individuals.emplace_back(copy2);
          break;
        }
      }
    }
    return ret;
  }
};