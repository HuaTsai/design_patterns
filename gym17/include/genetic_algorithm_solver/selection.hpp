#pragma once

#include <genetic_algorithm_solver/population.hpp>
#include <functional>

template <typename GeneType>
class Selection {
 public:
  Selection() = default;

  virtual ~Selection() = default;
  Selection(const Selection &) = delete;
  Selection &operator=(const Selection &) = delete;
  Selection(Selection &&) = delete;
  Selection &operator=(Selection &&) = delete;

  virtual Population<GeneType> operator()(const Population<GeneType> &population) const = 0;

  void set_fitness_function(const std::function<double(Individual<GeneType>)> &fitness_function) {
    fitness_function_ = fitness_function;
  }
  auto fitness_function() const { return fitness_function_; }

 private:
  std::function<double(Individual<GeneType>)> fitness_function_{nullptr};
};