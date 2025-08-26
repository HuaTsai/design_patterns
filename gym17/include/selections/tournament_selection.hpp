#include <genetic_algorithm_solver/selection.hpp>
#include <utility>

template <typename GeneType>
class TournamentSelection : public Selection<GeneType> {
 public:
  using Selection<GeneType>::Selection;

  Population<GeneType> operator()(const Population<GeneType> &population) const override {
    const int n = population.size();
    const int k = n / 2;  // tournament size
    std::vector<int> indices(n);
    std::iota(indices.begin(), indices.end(), 0);
    std::mt19937 gen(std::random_device{}());
    Population<GeneType> ret;
    while (std::cmp_less(ret.size(), n)) {
      std::shuffle(indices.begin(), indices.end(), gen);
      Population<GeneType> group;
      for (int i = 0; i < k; ++i) {
        group.individuals.emplace_back(population.individuals[indices[i]]);
      }

      auto it = std::ranges::max_element(group.individuals, [&](const Individual<GeneType> &a, const Individual<GeneType> &b) {
        return this->fitness_function()(a) < this->fitness_function()(b);
      });
      ret.individuals.emplace_back(*it);
    }
    return ret;
  }
};