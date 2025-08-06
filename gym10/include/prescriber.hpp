#pragma once

#include <prescription/prescription_handler.hpp>

class Prescriber {
 public:
  Prescriber();
  Prescription Prescribe(const Patient &patient, const std::vector<Symptom> &symptoms);
  void LoadSupportedPotentialDiseases(const std::string &filepath);

 private:
  std::shared_ptr<PrescriptionHandler> prescription_handler_;
};
