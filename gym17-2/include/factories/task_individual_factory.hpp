#pragma once

#include <genetic_algorithm_solver/individual_factory.hpp>
#include <individuals/task_individual.hpp>
#include <memory>

class TaskIndividualFactory : public IndividualFactory {
 public:
  std::shared_ptr<Individual> CreateCopiedIndividual(
      const std::shared_ptr<Individual> &individual) override {
    return std::make_shared<TaskIndividual>(*dynamic_pointer_cast<TaskIndividual>(individual));
  }
};