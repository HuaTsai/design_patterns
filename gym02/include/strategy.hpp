#pragma once

#include <memory>
#include <random>

#include "individual.hpp"

class Strategy {
 public:
  explicit Strategy(const std::vector<std::shared_ptr<Individual>> &individuals);
  virtual ~Strategy() = default;  // important!

  virtual std::shared_ptr<const Individual> MatchStrategy(
      std::shared_ptr<const Individual> individual) = 0;

  void Reverse() { reverse_ = !reverse_; }

 protected:
  std::vector<std::shared_ptr<Individual>> individuals_;
  bool reverse_;
  std::default_random_engine rng_;
};
