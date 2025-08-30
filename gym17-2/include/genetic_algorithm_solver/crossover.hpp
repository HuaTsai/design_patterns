#pragma once

#include <genetic_algorithm_solver/individual_factory.hpp>
#include <genetic_algorithm_solver/population.hpp>

class Crossover {
 public:
  explicit Crossover(const std::shared_ptr<IndividualFactory> &factory) : factory_(factory) {}

  virtual ~Crossover() = default;
  Crossover(const Crossover &) = delete;
  Crossover &operator=(const Crossover &) = delete;
  Crossover(Crossover &&) = delete;
  Crossover &operator=(Crossover &&) = delete;

  virtual std::shared_ptr<Population> operator()(
      const std::shared_ptr<Population> &parents) const = 0;

  std::shared_ptr<IndividualFactory> factory() const { return factory_; }

 private:
  std::shared_ptr<IndividualFactory> factory_;
};