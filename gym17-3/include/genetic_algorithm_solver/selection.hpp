#pragma once

#include <genetic_algorithm_solver/population.hpp>

class Selection {
 public:
  explicit Selection() {}

  virtual ~Selection() = default;
  Selection(const Selection &) = delete;
  Selection &operator=(const Selection &) = delete;
  Selection(Selection &&) = delete;
  Selection &operator=(Selection &&) = delete;

  virtual std::shared_ptr<Population> operator()(
      const std::shared_ptr<Population> &population) const = 0;
};