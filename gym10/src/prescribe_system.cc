#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>
#include <prescribe_system.hpp>

PrescribeSystem::PrescribeSystem(std::string dbpath, std::string supportpath) {
  prescriber_.LoadSupportedPotentialDiseases(supportpath);
  database_.LoadPatientsJsonFile(dbpath);
}

Prescription PrescribeSystem::Prescribe(std::string name, const std::vector<Symptom> &symptoms) {
  auto patient = database_.GetPatientByName(name);
  return prescriber_.Prescribe(patient, symptoms);
}

void PrescribeSystem::SavePrescriptionToFile(std::string filepath, std::string name,
                                             const Prescription &prescription) {
  const std::filesystem::path path(filepath);
  auto patient = database_.GetPatientByName(name);
  if (path.extension() == ".csv") {
    std::ofstream ofs(path);
    std::string medicines;
    for (size_t i = 0; i < prescription.medicines().size(); ++i) {
      medicines += prescription.medicines()[i];
      if (i + 1 != prescription.medicines().size()) {
        medicines += "、";
      }
    }
    ofs << "id,name,gender,age,height,weight,prescription,potential_disease,medicines,usage\n";
    ofs << patient.id() << "," << patient.name() << "," << GetStringFromGender(patient.gender())
        << "," << patient.age() << "," << patient.height() << "," << patient.weight() << ","
        << prescription.name() << "," << prescription.potential_disease() << "," << medicines << ","
        << prescription.usage() << "\n";
  } else if (path.extension() == ".json") {
    nlohmann::json j;
    j["id"] = patient.id();
    j["name"] = patient.name();
    j["gender"] = GetStringFromGender(patient.gender());
    j["age"] = patient.age();
    j["height"] = patient.height();
    j["weight"] = patient.weight();
    j["prescription"] = {{"name", prescription.name()},
                         {"potential_disease", prescription.potential_disease()},
                         {"medicines", prescription.medicines()},
                         {"usage", prescription.usage()}};
    std::ofstream ofs(path);
    ofs << j.dump(2);
    ofs.close();
  } else {
    throw std::invalid_argument("Unsupported file format");
  }
}

void PrescribeSystem::SaveCaseToDatabase(std::string filepath, std::string name, const Case &c) {
  auto &patient = database_.GetPatientByName(name);
  patient.AddCase(c);
  database_.SavePatientsJsonFile(filepath);
}
