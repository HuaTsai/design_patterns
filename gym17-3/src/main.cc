#include <crossovers/single_point_crossover.hpp>
#include <crossovers/two_point_crossover.hpp>
#include <crossovers/uniform_crossover.hpp>
#include <genetic_algorithm_solver/genetic_algorithm_solver.hpp>
#include <individuals/product_individual.hpp>
#include <individuals/task_individual.hpp>
#include <memory>
#include <mutates/inversion_mutate.hpp>
#include <mutates/random_replacement_mutate.hpp>
#include <numeric>
#include <print>
#include <selections/rank_selection.hpp>
#include <selections/tournament_selection.hpp>
#include <unordered_map>

void UsageScene1() {
  auto population = std::make_shared<Population>();
  for (int i = 0; i < 10; ++i) {
    auto individual = std::make_shared<TaskIndividual>();
    for (size_t j = 0; j < individual->size(); ++j) {
      individual->genes()[j] = individual->GenerateRandomGene();
    }
    population->individuals.push_back(individual);
  }

  auto selection = std::make_shared<TournamentSelection>();
  auto crossover = std::make_shared<TwoPointCrossover>();
  auto mutate = std::make_shared<RandomReplacementMutate>();
  const int max_iterations = 10000;
  GeneticAlgorithmSolver solver(selection, crossover, mutate, max_iterations);
  auto res = solver.GeneticAlgorithm(population);

  std::print("Scheduling Problem Solution:\n");
  for (size_t i = 0; i < res->genes().size(); ++i) {
    auto task = std::any_cast<Task>(res->genes()[i]);
    if (i < 100) {
      std::print("- A #{:03d}:", i);
    } else if (i < 300) {
      std::print("- B #{:03d}:", i);
    } else {
      std::print("- C #{:03d}:", i);
    }
    std::print(" worker: {}, machine: {}\n", task.worker, task.machine);
  }
  std::print("Fitness: {}\n", res->Fitness());
}

void UsageScene2() {
  auto population = std::make_shared<Population>();
  auto ind1 = std::make_shared<ProductIndividual>();
  ind1->genes() = {7, 0, 0, 0, 0, 0};
  auto ind2 = std::make_shared<ProductIndividual>();
  ind2->genes() = {0, 3, 0, 0, 0, 0};
  auto ind3 = std::make_shared<ProductIndividual>();
  ind3->genes() = {0, 0, 3, 0, 0, 0};
  auto ind4 = std::make_shared<ProductIndividual>();
  ind4->genes() = {0, 0, 0, 2, 0, 0};
  auto ind5 = std::make_shared<ProductIndividual>();
  ind5->genes() = {0, 0, 0, 0, 2, 0};
  auto ind6 = std::make_shared<ProductIndividual>();
  ind6->genes() = {0, 0, 0, 0, 0, 2};
  population->individuals = {ind1, ind2, ind3, ind4, ind5, ind6};

  auto selection = std::make_shared<RankSelection>();
  auto crossover = std::make_shared<SinglePointCrossover>();
  auto mutate = std::make_shared<RandomReplacementMutate>();
  const int max_iterations = 10000;
  GeneticAlgorithmSolver solver(selection, crossover, mutate, max_iterations);

  auto res = solver.GeneticAlgorithm(population);
  std::print("Product Suggestion Solution:\n");
  for (size_t i = 0; i < res->genes().size(); ++i) {
    int count = std::any_cast<int>(res->genes()[i]);
    std::print("- {}: {}\n", static_cast<char>('A' + i), count);
  }
  std::print("Fitness: {}\n", res->Fitness());
}

int main() {
  UsageScene1();
  std::print("\n");
  UsageScene2();
}