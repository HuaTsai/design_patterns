#pragma once

#include <genetic_algorithm_solver/mutate.hpp>
#include <random>

class RandomReplacementMutate : public Mutate {
 public:
  using Mutate::Mutate;

  std::shared_ptr<Population> operator()(
      const std::shared_ptr<Population> &offspring) const override {
    static std::mt19937 gen(std::random_device{}());
    std::bernoulli_distribution ber(0.05);  // small chance of mutation

    auto mutated = std::make_shared<Population>();
    for (const auto &individual : offspring->individuals) {
      while (true) {
        auto candidate = factory()->CreateCopiedIndividual(individual);
        for (auto &gene : candidate->genes()) {
          if (ber(gen)) {
            gene = candidate->GenerateRandomGene();
          }
        }
        if (candidate->IsValid()) {
          mutated->individuals.emplace_back(candidate);
          break;
        }
      }
    }
    return mutated;
  }
};