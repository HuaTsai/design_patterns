#pragma once

#include <genetic_algorithm_solver/population.hpp>

class Crossover {
 public:
  explicit Crossover() {}

  virtual ~Crossover() = default;
  Crossover(const Crossover &) = delete;
  Crossover &operator=(const Crossover &) = delete;
  Crossover(Crossover &&) = delete;
  Crossover &operator=(Crossover &&) = delete;

  virtual std::shared_ptr<Population> operator()(
      const std::shared_ptr<Population> &parents) const = 0;
};