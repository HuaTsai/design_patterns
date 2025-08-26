#pragma once

#include <functional>
#include <genetic_algorithm_solver/population.hpp>

template <typename GeneType>
class Crossover {
 public:
  Crossover() = default;

  virtual ~Crossover() = default;
  Crossover(const Crossover &) = delete;
  Crossover &operator=(const Crossover &) = delete;
  Crossover(Crossover &&) = delete;
  Crossover &operator=(Crossover &&) = delete;

  virtual Population<GeneType> operator()(const Population<GeneType> &parents) const = 0;

  void set_is_valid(const std::function<bool(const Individual<GeneType> &)> &is_valid) {
    is_valid_ = is_valid;
  }
  auto is_valid() const { return is_valid_; }

 private:
  std::function<bool(const Individual<GeneType> &)> is_valid_{nullptr};
};