#pragma once

#include <genetic_algorithm_solver/population.hpp>

class Mutate {
 public:
  explicit Mutate() {}

  virtual ~Mutate() = default;
  Mutate(const Mutate &) = delete;
  Mutate &operator=(const Mutate &) = delete;
  Mutate(Mutate &&) = delete;
  Mutate &operator=(Mutate &&) = delete;

  virtual std::shared_ptr<Population> operator()(
      const std::shared_ptr<Population> &offspring) const = 0;
};