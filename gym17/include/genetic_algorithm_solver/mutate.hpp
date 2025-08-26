#pragma once

#include <genetic_algorithm_solver/population.hpp>

template <typename GeneType>
class Mutate {
 public:
  explicit Mutate(const std::vector<GeneType> &options) : options_(options) {}

  virtual ~Mutate() = default;
  Mutate(const Mutate &) = delete;
  Mutate &operator=(const Mutate &) = delete;
  Mutate(Mutate &&) = delete;
  Mutate &operator=(Mutate &&) = delete;

  virtual Population<GeneType> operator()(const Population<GeneType> &offspring) const = 0;

  std::vector<GeneType> options() const { return options_; }
  void set_is_valid(const std::function<bool(const Individual<GeneType> &)> &is_valid) {
    is_valid_ = is_valid;
  }
  auto is_valid() const { return is_valid_; }

 private:
  std::function<bool(const Individual<GeneType> &)> is_valid_{nullptr};
  std::vector<GeneType> options_;
};