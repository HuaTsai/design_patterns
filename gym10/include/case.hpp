#pragma once

#include <prescription/prescription.hpp>
#include <symptom.hpp>
#include <vector>

class Case {
 public:
  Case(int case_time, std::vector<Symptom> symptoms, Prescription prescription);

  int case_time() const { return case_time_; }
  const std::vector<Symptom> &symptoms() const { return symptoms_; }
  const Prescription &prescription() const { return prescription_; }

 private:
  int case_time_;
  std::vector<Symptom> symptoms_;
  Prescription prescription_;
};
