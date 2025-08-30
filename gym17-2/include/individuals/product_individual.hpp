#pragma once

#include <genetic_algorithm_solver/individual.hpp>
#include <numeric>
#include <random>

class ProductIndividual : public Individual {
  static constexpr size_t kNumGenes = 6;

 public:
  ProductIndividual() : Individual() { genes() = {0, 0, 0, 0, 0, 0}; }

  size_t size() const override { return kNumGenes; }

  bool IsValid() const override {
    if (genes().size() != kNumGenes) {
      return false;
    }
    const std::vector<int> weights{2, 3, 5, 4, 6, 7};
    const std::vector<int> prices{100, 200, 150, 300, 180, 250};
    int total_weight = 0;
    int total_price = 0;
    for (size_t i = 0; i < kNumGenes; ++i) {
      int count = std::any_cast<int>(genes()[i]);
      if (count < 0) {
        return false;
      }
      total_weight += count * weights[i];
      total_price += count * prices[i];
    }
    return total_weight <= 15 && total_price <= 700;
  }

  double Fitness() const override {
    return 0.8 * (std::any_cast<int>(genes()[0]) + std::any_cast<int>(genes()[1])) +
           0.6 * (std::any_cast<int>(genes()[2]) + std::any_cast<int>(genes()[3])) +
           0.2 * (std::any_cast<int>(genes()[4]) + std::any_cast<int>(genes()[5]));
  }

  std::any GenerateRandomGene() const override {
    static std::mt19937 gen{std::random_device{}()};
    std::uniform_int_distribution<> dis(0, 7);
    return dis(gen);
  }
};