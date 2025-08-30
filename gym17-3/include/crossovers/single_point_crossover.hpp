#pragma once

#include <algorithm>
#include <genetic_algorithm_solver/crossover.hpp>
#include <numeric>
#include <random>

class SinglePointCrossover : public Crossover {
 public:
  using Crossover::Crossover;

  std::shared_ptr<Population> operator()(
      const std::shared_ptr<Population> &parents) const override {
    int n = parents->size();
    int n_genes = parents->individuals[0]->size();
    static std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<> dis(0, n_genes - 1);
    std::vector<int> indices(n);
    std::ranges::iota(indices, 0);
    std::ranges::shuffle(indices, gen);

    auto ret = std::make_shared<Population>();
    for (int i = 0; i < n; i += 2) {
      if (i + 1 == n) {
        auto copy = parents->individuals[indices[i]]->Clone();
        ret->individuals.emplace_back(copy);
        break;
      }

      int retry = 0;
      while (true) {
        auto offspring1 = parents->individuals[indices[i]]->Clone();
        auto offspring2 = parents->individuals[indices[i + 1]]->Clone();
        for (int j = dis(gen); j < n_genes; ++j) {
          std::swap(offspring1->genes()[j], offspring2->genes()[j]);
        }

        if (offspring1->IsValid() && offspring2->IsValid()) {
          ret->individuals.emplace_back(offspring1);
          ret->individuals.emplace_back(offspring2);
          break;
        }

        if (++retry == 100) {
          auto copy1 = parents->individuals[indices[i]]->Clone();
          auto copy2 = parents->individuals[indices[i + 1]]->Clone();
          ret->individuals.emplace_back(copy1);
          ret->individuals.emplace_back(copy2);
          break;
        }
      }
    }
    return ret;
  }
};