#pragma once

#include <string>
#include <vector>

class Prescription {
 public:
  Prescription(const std::string &name, const std::string &potential_disease,
               const std::vector<std::string> &medicines, const std::string &usage);

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
