#pragma once

#include <genetic_algorithm_solver/individual_factory.hpp>
#include <genetic_algorithm_solver/population.hpp>

class Mutate {
 public:
  explicit Mutate(const std::shared_ptr<IndividualFactory> &factory) : factory_(factory) {}

  virtual ~Mutate() = default;
  Mutate(const Mutate &) = delete;
  Mutate &operator=(const Mutate &) = delete;
  Mutate(Mutate &&) = delete;
  Mutate &operator=(Mutate &&) = delete;

  virtual std::shared_ptr<Population> operator()(
      const std::shared_ptr<Population> &offspring) const = 0;

  std::shared_ptr<IndividualFactory> factory() const { return factory_; }

 private:
  std::shared_ptr<IndividualFactory> factory_;
};