#pragma once

#include <memory>
#include <random>

#include "individual.hpp"

class Strategy {
 public:
  explicit Strategy(const std::vector<std::shared_ptr<Individual>> &individuals);

  virtual ~Strategy() = default;  // important!
  Strategy(const Strategy &) = delete;
  Strategy &operator=(const Strategy &) = delete;
  Strategy(Strategy &&) = delete;
  Strategy &operator=(Strategy &&) = delete;

  virtual std::shared_ptr<const Individual> MatchStrategy(
      std::shared_ptr<const Individual> individual) = 0;

  void Reverse() { reverse_ = !reverse_; }

  std::vector<std::shared_ptr<Individual>> individuals() const { return individuals_; }
  bool reverse() const { return reverse_; }
  std::default_random_engine rng() const { return rng_; }

 private:
  std::vector<std::shared_ptr<Individual>> individuals_;
  bool reverse_;
  std::default_random_engine rng_;
};
