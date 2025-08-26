#include <genetic_algorithm_solver/mutate.hpp>

template <typename GeneType>
class RandomReplacementMutate : public Mutate<GeneType> {
 public:
  using Mutate<GeneType>::Mutate;

  Population<GeneType> operator()(const Population<GeneType> &offspring) const override {
    int n = this->options().size();
    std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<> dis(0, n - 1);
    std::bernoulli_distribution ber(0.05);  // small chance of mutation

    Population<GeneType> mutated;
    for (const auto &individual : offspring.individuals) {
      while (true) {
        auto candidate = individual;
        for (auto &gene : candidate.genes) {
          if (ber(gen)) {
            gene = this->options()[dis(gen)];
          }
        }
        if (!this->is_valid() || this->is_valid()(candidate)) {
          mutated.individuals.emplace_back(candidate);
          break;
        }
      }
    }
    return mutated;
  }
};