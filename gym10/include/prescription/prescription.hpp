#pragma once

#include <string>
#include <vector>

class Prescription {
 public:
  Prescription(std::string name, std::string potential_disease, std::vector<std::string> medicines,
               std::string usage);

  std::string name() const { return name_; }
  std::string potential_disease() const { return potential_disease_; }
  std::vector<std::string> medicines() const { return medicines_; }
  std::string usage() const { return usage_; }

 private:
  std::string name_;
  std::string potential_disease_;
  std::vector<std::string> medicines_;
  std::string usage_;
};
