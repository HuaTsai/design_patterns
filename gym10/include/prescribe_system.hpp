#pragma once

#include <patient_database.hpp>
#include <prescriber.hpp>

class PrescribeSystem {
 public:
  PrescribeSystem(std::string dbpath, std::string supportpath);
  Prescription Prescribe(std::string name, const std::vector<Symptom> &symptoms);
  void SavePrescriptionToFile(std::string filepath, std::string name,
                              const Prescription &prescription);
  void SaveCaseToDatabase(std::string filepath, std::string name, const Case &c);

 private:
  Prescriber prescriber_;
  PatientDatabase database_;
};
