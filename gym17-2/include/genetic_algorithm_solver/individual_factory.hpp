#pragma once

#include <genetic_algorithm_solver/individual.hpp>
#include <memory>

class IndividualFactory {
 public:
  IndividualFactory() = default;

  virtual ~IndividualFactory() = default;
  IndividualFactory(const IndividualFactory &) = delete;
  IndividualFactory &operator=(const IndividualFactory &) = delete;
  IndividualFactory(IndividualFactory &&) = delete;
  IndividualFactory &operator=(IndividualFactory &&) = delete;

  virtual std::shared_ptr<Individual> CreateCopiedIndividual(
      const std::shared_ptr<Individual> &individual) = 0;
};