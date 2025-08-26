#include <genetic_algorithm_solver/mutate.hpp>

template <typename GeneType>
class InversionMutate : public Mutate<GeneType> {
 public:
  InversionMutate() : Mutate<GeneType>({}) {}

 private:
  Population<GeneType> operator()(const Population<GeneType> &offspring) const override {
    int n = offspring.individuals[0].genes.size();
    std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<> dis(0, n - 1);

    Population<GeneType> mutated;
    for (const auto &individual : offspring.individuals) {
      int retry = 0;
      while (true) {
        auto candidate = individual;
        int x1 = dis(gen);
        int x2 = dis(gen);
        if (x1 > x2) {
          std::swap(x1, x2);
        }
        std::reverse(candidate.genes.begin() + x1, candidate.genes.begin() + x2 + 1);
        if (!this->is_valid() || this->is_valid()(candidate)) {
          mutated.individuals.emplace_back(candidate);
          break;
        }
        
        if (++retry == 100) {
          mutated.individuals.emplace_back(individual);
          break;
        }
      }
    }
    return mutated;
  }
};