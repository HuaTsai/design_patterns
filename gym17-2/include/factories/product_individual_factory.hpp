#pragma once

#include <genetic_algorithm_solver/individual_factory.hpp>
#include <individuals/product_individual.hpp>
#include <memory>

class ProductIndividualFactory : public IndividualFactory {
 public:
  std::shared_ptr<Individual> CreateCopiedIndividual(
      const std::shared_ptr<Individual> &individual) override {
    return std::make_shared<ProductIndividual>(
        *dynamic_pointer_cast<ProductIndividual>(individual));
  }
};