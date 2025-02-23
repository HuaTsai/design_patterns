#pragma once

#include "strategy.hpp"

class DistanceStrategy : public Strategy {
 public:
  using Strategy::Strategy;

  std::shared_ptr<const Individual> MatchStrategy(
      std::shared_ptr<const Individual> individual) override;
};
