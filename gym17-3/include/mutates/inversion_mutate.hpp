#pragma once

#include <algorithm>
#include <genetic_algorithm_solver/mutate.hpp>
#include <random>

class InversionMutate : public Mutate {
 public:
  using Mutate::Mutate;

 private:
  std::shared_ptr<Population> operator()(
      const std::shared_ptr<Population> &offspring) const override {
    int n = offspring->individuals[0]->size();
    static std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<> dis(0, n - 1);

    auto mutated = std::make_shared<Population>();
    for (const auto &individual : offspring->individuals) {
      int retry = 0;
      while (true) {
        auto candidate = individual->Clone();
        int x1 = dis(gen);
        int x2 = dis(gen);
        if (x1 > x2) {
          std::swap(x1, x2);
        }
        std::reverse(candidate->genes().begin() + x1, candidate->genes().begin() + x2 + 1);
        if (candidate->IsValid()) {
          mutated->individuals.emplace_back(candidate);
          break;
        }

        if (++retry == 100) {
          mutated->individuals.emplace_back(individual);
          break;
        }
      }
    }
    return mutated;
  }
};