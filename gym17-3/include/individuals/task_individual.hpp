#pragma once

#include <algorithm>
#include <genetic_algorithm_solver/individual.hpp>
#include <random>
#include <unordered_map>

struct Task {
  int worker;
  int machine;
};

class TaskIndividual : public Individual {
  static constexpr int kNumTasks = 600;
  static constexpr int kNumWorkers = 4;
  static constexpr int kNumMachines = 2;

 public:
  TaskIndividual() : Individual() { genes().assign(kNumTasks, Task{.worker = 0, .machine = 0}); }

  size_t size() const override { return kNumTasks; }

  std::shared_ptr<Individual> Clone() const override {
    return std::make_shared<TaskIndividual>(*this);
  }

  bool IsValid() const override {
    if (genes().size() != kNumTasks) {
      return false;
    }
    return std::ranges::all_of(genes(), [](const auto &gene) {
      auto task = std::any_cast<Task>(gene);
      return task.worker >= 0 && task.worker < kNumWorkers && task.machine >= 0 &&
             task.machine < kNumMachines;
    });
  }

  double Fitness() const override {
    std::unordered_map<int, int> worker_hours;
    std::unordered_map<int, int> machine_hours;
    for (int i = 0; i < kNumTasks; ++i) {
      auto task = std::any_cast<Task>(genes()[i]);
      if (i < 100) {
        worker_hours[task.worker] += 2;
        machine_hours[task.machine] += 2;
      } else if (i < 300) {
        worker_hours[task.worker] += 4;
        machine_hours[task.machine] += 4;
      } else {
        worker_hours[task.worker] += 6;
        machine_hours[task.machine] += 6;
      }
    }
    auto max_worker = std::ranges::max_element(
        worker_hours, [](const auto &a, const auto &b) { return a.second < b.second; });
    auto max_machine = std::ranges::max_element(
        machine_hours, [](const auto &a, const auto &b) { return a.second < b.second; });
    return -std::max(max_worker->second, max_machine->second);
  }

  std::any GenerateRandomGene() const override {
    static std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<> disworker(0, kNumWorkers - 1);
    std::uniform_int_distribution<> dismachine(0, kNumMachines - 1);
    return Task{.worker = disworker(gen), .machine = dismachine(gen)};
  }
};