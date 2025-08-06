#pragma once

#include <patient_database.hpp>
#include <prescriber.hpp>

class PrescribeSystem {
 public:
  PrescribeSystem(const std::string& dbpath, const std::string& supportpath);
  Prescription Prescribe(const std::string& name, const std::vector<Symptom> &symptoms);
  void SavePrescriptionToFile(const std::string& filepath, const std::string& name,
                              const Prescription &prescription);
  void SaveCaseToDatabase(const std::string& filepath, const std::string& name, const Case &c);

 private:
  Prescriber prescriber_;
  PatientDatabase database_;
};
