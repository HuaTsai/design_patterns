#include <algorithm>
#include <numeric>
#include <genetic_algorithm_solver/selection.hpp>

template <typename GeneType>
class RankSelection : public Selection<GeneType> {
 public:
  using Selection<GeneType>::Selection;

  Population<GeneType> operator()(const Population<GeneType> &population) const override {
    const double sp = 1.5;  // selection pressure
    int n = population.size();
    std::vector<double> probs(n);
    for (int i = 0; i < n; ++i) {
      probs[i] = 1. / n * (sp - (2 * sp - 2) * i / (n - 1));
    }
    std::vector<double> cumulative_probs(n);
    std::partial_sum(probs.begin(), probs.end(), cumulative_probs.begin());

    auto sorted_population = population;
    std::ranges::sort(sorted_population,
                      [this](const Individual<GeneType> &a, const Individual<GeneType> &b) {
                        return this->fitness_function()(a) > this->fitness_function()(b);
                      });

    std::mt19937 gen(std::random_device{}());
    std::uniform_real_distribution<> dis(0, cumulative_probs.back());

    Population<GeneType> selected;
    for (int i = 0; i < n; ++i) {
      double p = dis(gen);
      auto it = std::ranges::lower_bound(cumulative_probs, p);
      int index = std::distance(cumulative_probs.begin(), it);
      selected.individuals.emplace_back(sorted_population.individuals[index]);
    }
    return selected;
  }
};