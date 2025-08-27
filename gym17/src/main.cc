#include <crossovers/single_point_crossover.hpp>
#include <crossovers/two_point_crossover.hpp>
#include <crossovers/uniform_crossover.hpp>
#include <genetic_algorithm_solver/genetic_algorithm_solver.hpp>
#include <memory>
#include <mutates/inversion_mutate.hpp>
#include <mutates/random_replacement_mutate.hpp>
#include <print>
#include <selections/rank_selection.hpp>
#include <selections/tournament_selection.hpp>

void UsageScene1() {
  // Each schedule/individual has 600 tasks/genes
  // NOLINTBEGIN
  struct Task {
    Task(int m, int w) : machine(m), worker(w) {}
    int machine;  // 0, 1
    int worker;   // 0, 1, 2, 3
  };
  // NOLINTEND
  const Population<Task> population{
      .individuals = {Individual<Task>{.genes = std::vector<Task>(600, Task(0, 0))},
                      Individual<Task>{.genes = std::vector<Task>(600, Task(0, 1))},
                      Individual<Task>{.genes = std::vector<Task>(600, Task(0, 2))},
                      Individual<Task>{.genes = std::vector<Task>(600, Task(0, 3))},
                      Individual<Task>{.genes = std::vector<Task>(600, Task(1, 0))},
                      Individual<Task>{.genes = std::vector<Task>(600, Task(1, 1))},
                      Individual<Task>{.genes = std::vector<Task>(600, Task(1, 2))},
                      Individual<Task>{.genes = std::vector<Task>(600, Task(1, 3))}}};
  auto selection = std::make_shared<TournamentSelection<Task>>();
  auto crossover = std::make_shared<TwoPointCrossover<Task>>();
  std::vector<Task> options;
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 4; ++j) {
      options.emplace_back(i, j);
    }
  }
  auto mutate = std::make_shared<RandomReplacementMutate<Task>>(options);
  const auto fitness_function = [](const Individual<Task> &x) -> double {
    std::unordered_map<int, int> machine_hours;
    std::unordered_map<int, int> worker_hours;
    for (int i = 0; i < 600; ++i) {
      int hours = 0;
      if (i < 100) {
        hours = 2;
      } else if (i < 300) {
        hours = 4;
      } else {
        hours = 6;
      }
      machine_hours[x.genes[i].machine] += hours;
      worker_hours[x.genes[i].worker] += hours;
    }
    auto max_machine = std::ranges::max_element(
        machine_hours, [](const auto &a, const auto &b) { return a.second < b.second; });
    auto max_worker = std::ranges::max_element(
        worker_hours, [](const auto &a, const auto &b) { return a.second < b.second; });
    return -std::max(max_machine->second, max_worker->second);
  };
  const int max_iterations = 10000;
  GeneticAlgorithmSolver<Task> solver(selection, crossover, mutate, nullptr, fitness_function,
                                      max_iterations);
  auto res = solver.GeneticAlgorithm(population);
  std::print("Scheduling Problem Solution:\n");
  for (size_t i = 0; i < res.genes.size(); ++i) {
    if (i < 100) {
      std::print("- A #{:03d}:", i);
    } else if (i < 300) {
      std::print("- B #{:03d}:", i);
    } else {
      std::print("- C #{:03d}:", i);
    }
    std::print(" m {} + w {}\n", res.genes[i].machine, res.genes[i].worker);
  }
  std::print("Fitness: {}\n", fitness_function(res));
}

void UsageScene2() {
  const Population<int> population{.individuals = {Individual<int>{.genes = {7, 0, 0, 0, 0, 0}},
                                                   Individual<int>{.genes = {0, 3, 0, 0, 0, 0}},
                                                   Individual<int>{.genes = {0, 0, 3, 0, 0, 0}},
                                                   Individual<int>{.genes = {0, 0, 0, 2, 0, 0}},
                                                   Individual<int>{.genes = {0, 0, 0, 0, 2, 0}},
                                                   Individual<int>{.genes = {0, 0, 0, 0, 0, 2}}}};
  auto selection = std::make_shared<RankSelection<int>>();
  auto crossover = std::make_shared<SinglePointCrossover<int>>();
  auto mutate =
      std::make_shared<RandomReplacementMutate<int>>(std::vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8});
  const auto is_valid = [](const Individual<int> &x) -> bool {
    std::vector<int> weights{2, 3, 5, 4, 6, 7};
    std::vector<int> prices{100, 200, 150, 300, 180, 250};
    return std::inner_product(weights.begin(), weights.end(), x.genes.begin(), 0) <= 15 &&
           std::inner_product(prices.begin(), prices.end(), x.genes.begin(), 0) <= 700;
  };
  const auto fitness_function = [](const Individual<int> &x) -> double {
    return 0.8 * (x.genes[0] + x.genes[1]) + 0.6 * (x.genes[2] + x.genes[3]) +
           0.2 * (x.genes[4] + x.genes[5]);
  };
  const int max_iterations = 10000;
  GeneticAlgorithmSolver<int> solver(selection, crossover, mutate, is_valid, fitness_function,
                                     max_iterations);

  auto res = solver.GeneticAlgorithm(population);
  std::print("Product Suggestion Solution:\n");
  for (size_t i = 0; i < res.genes.size(); ++i) {
    std::print("- {}: {}\n", static_cast<char>('A' + i), res.genes[i]);
  }
  std::print("Fitness: {}\n", fitness_function(res));
}

int main() {
  UsageScene1();
  std::print("\n");
  UsageScene2();
}