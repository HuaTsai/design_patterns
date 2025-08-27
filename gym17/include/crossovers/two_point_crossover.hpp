#include <algorithm>
#include <genetic_algorithm_solver/crossover.hpp>
#include <random>

template <typename GeneType>
class TwoPointCrossover : public Crossover<GeneType> {
 public:
  using Crossover<GeneType>::Crossover;

  Population<GeneType> operator()(const Population<GeneType> &parents) const override {
    int n = parents.size();
    int n_genes = parents.individuals[0].genes.size();
    std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<> dis(0, n_genes - 1);
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
        int x1 = dis(gen);
        int x2 = dis(gen);
        if (x1 > x2) {
          std::swap(x1, x2);
        }

        auto offspring1 = parents.individuals[indices[i]];
        auto offspring2 = parents.individuals[indices[i + 1]];
        for (int j = x1; j <= x2; ++j) {
          std::swap(offspring1.genes[j], offspring2.genes[j]);
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