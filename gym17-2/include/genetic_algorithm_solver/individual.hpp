#pragma once

#include <any>
#include <vector>

class Individual {
 public:
  Individual() = default;

  virtual ~Individual() = default;
  Individual(const Individual &) = default;
  Individual &operator=(const Individual &) = default;
  Individual(Individual &&) = default;
  Individual &operator=(Individual &&) = default;

  virtual size_t size() const = 0;
  virtual bool IsValid() const = 0;
  virtual double Fitness() const = 0;
  virtual std::any GenerateRandomGene() const = 0;

  const std::vector<std::any> &genes() const { return genes_; }
  std::vector<std::any> &genes() { return genes_; }

 private:
  std::vector<std::any> genes_;
};