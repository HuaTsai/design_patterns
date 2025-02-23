#pragma once

#include "individual.hpp"
#include "strategy.hpp"

class System {
 public:
  System(const std::vector<std::shared_ptr<Individual>> &individuals,
         std::shared_ptr<Strategy> strategy);

  std::shared_ptr<const Individual> Match(std::shared_ptr<const Individual> individual);

 private:
  std::vector<std::shared_ptr<Individual>> individuals_;
  std::shared_ptr<Strategy> strategy_;
};
