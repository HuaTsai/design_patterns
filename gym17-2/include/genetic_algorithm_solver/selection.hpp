#pragma once

#include <genetic_algorithm_solver/individual_factory.hpp>
#include <genetic_algorithm_solver/population.hpp>

class Selection {
 public:
  explicit Selection(const std::shared_ptr<IndividualFactory> &factory) : factory_(factory) {}

  virtual ~Selection() = default;
  Selection(const Selection &) = delete;
  Selection &operator=(const Selection &) = delete;
  Selection(Selection &&) = delete;
  Selection &operator=(Selection &&) = delete;

  virtual std::shared_ptr<Population> operator()(
      const std::shared_ptr<Population> &population) const = 0;

  std::shared_ptr<IndividualFactory> factory() const { return factory_; }

 private:
  std::shared_ptr<IndividualFactory> factory_;
};