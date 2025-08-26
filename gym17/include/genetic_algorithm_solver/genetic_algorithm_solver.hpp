#pragma once

#include <genetic_algorithm_solver/crossover.hpp>
#include <genetic_algorithm_solver/mutate.hpp>
#include <genetic_algorithm_solver/population.hpp>
#include <genetic_algorithm_solver/selection.hpp>
#include <memory>

template <typename GeneType>
class GeneticAlgorithmSolver {
 public:
  explicit GeneticAlgorithmSolver(
      std::shared_ptr<Selection<GeneType>> selection,
      std::shared_ptr<Crossover<GeneType>> crossover, std::shared_ptr<Mutate<GeneType>> mutate,
      const std::function<bool(const Individual<GeneType> &)> &is_valid,
      const std::function<double(Individual<GeneType>)> &fitness_function, int max_iterations)
      : selection_(selection),
        crossover_(crossover),
        mutate_(mutate),
        is_valid_(is_valid),
        fitness_function_(fitness_function),
        max_iterations_(max_iterations) {
    selection_->set_fitness_function(fitness_function);
    crossover_->set_is_valid(is_valid);
    mutate_->set_is_valid(is_valid);
  }

  Individual<GeneType> GeneticAlgorithm(const Population<GeneType> &population) {
    Population<GeneType> filtered_population;
    for (const auto &individual : population.individuals) {
      if (!is_valid_ || is_valid_(individual)) {
        filtered_population.individuals.emplace_back(individual);
      }
    }

    auto best_individual = FindBestIndividual(filtered_population);
    auto curr = filtered_population;
    for (int i = 0; i < max_iterations_; ++i) {
      auto parents = (*selection_)(curr);
      auto offspring = (*crossover_)(parents);
      curr = (*mutate_)(offspring);
      auto local_best = FindBestIndividual(curr);
      if (fitness_function_(local_best) > fitness_function_(best_individual)) {
        best_individual = local_best;
      }
    }
    return best_individual;
  }

  Individual<GeneType> FindBestIndividual(const Population<GeneType> &population) {
    auto best_it =
        std::ranges::max_element(population.individuals, [this](const auto &a, const auto &b) {
          return fitness_function_(a) < fitness_function_(b);
        });
    return *best_it;
  }

 private:
  std::shared_ptr<Selection<GeneType>> selection_;
  std::shared_ptr<Crossover<GeneType>> crossover_;
  std::shared_ptr<Mutate<GeneType>> mutate_;
  std::function<bool(const Individual<GeneType> &)> is_valid_;
  std::function<double(Individual<GeneType>)> fitness_function_;
  int max_iterations_;
};
