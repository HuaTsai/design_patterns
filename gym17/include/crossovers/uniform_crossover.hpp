#include <algorithm>
#include <genetic_algorithm_solver/crossover.hpp>
#include <random>

template <typename GeneType>
class UniformCrossover : public Crossover<GeneType> {
 public:
  using Crossover<GeneType>::Crossover;

  Population<GeneType> operator()(const Population<GeneType> &parents) const override {
    int n = parents.size();
    std::mt19937 gen(std::random_device{}());
    std::bernoulli_distribution dis(0.5);
    std::vector<int> indices(n);
    std::ranges::iota(indices, 0);
    std::ranges::shuffle(indices, gen);

    Population<GeneType> ret;
    for (int i = 0; i < n; i += 2) {
      if (i + 1 == n) {
        ret.individuals.emplace_back(parents.individuals[indices[i]]);
        break;
      }

      int retry = 0;
      while (true) {
        auto offspring1 = parents.individuals[indices[i]];
        auto offspring2 = parents.individuals[indices[i + 1]];
        for (size_t j = 0; j < offspring1.genes.size(); ++j) {
          if (dis(gen)) {
            std::swap(offspring1.genes[j], offspring2.genes[j]);
          }
        }

        if (!this->is_valid() || (this->is_valid()(offspring1) && this->is_valid()(offspring2))) {
          ret.individuals.emplace_back(offspring1);
          ret.individuals.emplace_back(offspring2);
          break;
        }

        if (++retry == 100) {
          ret.individuals.emplace_back(parents.individuals[indices[i]]);
          ret.individuals.emplace_back(parents.individuals[indices[i + 1]]);
          break;
        }
      }
    }
    return ret;
  }
};