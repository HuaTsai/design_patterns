#pragma once

#include <case.hpp>
#include <patient.hpp>
#include <unordered_map>

class PatientDatabase {
 public:
  Patient &GetPatientByName(const std::string &name);
  void LoadPatientsJsonFile(const std::string &dbpath);
  void SavePatientsJsonFile(const std::string &dbpath);

 private:
  std::unordered_map<std::string, Patient> patients_;
};
