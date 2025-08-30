#pragma once

#include <algorithm>
#include <genetic_algorithm_solver/crossover.hpp>
#include <genetic_algorithm_solver/individual_factory.hpp>
#include <genetic_algorithm_solver/mutate.hpp>
#include <genetic_algorithm_solver/population.hpp>
#include <genetic_algorithm_solver/selection.hpp>
#include <memory>

class GeneticAlgorithmSolver {
 public:
  explicit GeneticAlgorithmSolver(const std::shared_ptr<IndividualFactory> &factory,
                                  const std::shared_ptr<Selection> &selection,
                                  const std::shared_ptr<Crossover> &crossover,
                                  const std::shared_ptr<Mutate> &mutate, int max_iterations)
      : factory_(factory),
        selection_(selection),
        crossover_(crossover),
        mutate_(mutate),
        max_iterations_(max_iterations) {}

  std::shared_ptr<Individual> GeneticAlgorithm(const std::shared_ptr<Population> &population) {
    auto filtered_population = std::make_shared<Population>();
    for (const auto &individual : population->individuals) {
      if (individual->IsValid()) {
        auto copy = factory_->CreateCopiedIndividual(individual);
        filtered_population->individuals.emplace_back(copy);
      }
    }

    auto best_individual = FindBestIndividual(filtered_population);
    auto curr = filtered_population;
    for (int i = 0; i < max_iterations_; ++i) {
      auto parents = (*selection_)(curr);
      auto offspring = (*crossover_)(parents);
      curr = (*mutate_)(offspring);
      auto local_best = FindBestIndividual(curr);
      if (local_best->Fitness() > best_individual->Fitness()) {
        best_individual = local_best;
      }
    }
    return best_individual;
  }

  std::shared_ptr<Individual> FindBestIndividual(const std::shared_ptr<Population> &population) {
    return *std::ranges::max_element(
        population->individuals,
        [](const std::shared_ptr<Individual> &a, const std::shared_ptr<Individual> &b) {
          return a->Fitness() < b->Fitness();
        });
  }

 private:
  std::shared_ptr<IndividualFactory> factory_;
  std::shared_ptr<Selection> selection_;
  std::shared_ptr<Crossover> crossover_;
  std::shared_ptr<Mutate> mutate_;
  int max_iterations_;
};
