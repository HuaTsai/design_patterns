#pragma once

#include <case.hpp>
#include <patient.hpp>
#include <unordered_map>

class PatientDatabase {
 public:
  Patient &GetPatientByName(std::string name);
  void LoadPatientsJsonFile(std::string dbpath);
  void SavePatientsJsonFile(std::string dbpath);

 private:
  std::unordered_map<std::string, Patient> patients_;
};
