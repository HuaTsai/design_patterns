#include <fstream>
#include <nlohmann/json.hpp>
#include <patient_database.hpp>

Patient &PatientDatabase::GetPatientByName(std::string name) {
  for (auto &[id, p] : patients_) {
    if (p.name() == name) {
      return p;
    }
  }
  throw std::runtime_error("Patient name " + name + " not found.");
}

void PatientDatabase::LoadPatientsJsonFile(std::string dbpath) {
  if (!std::filesystem::exists(dbpath)) {
    throw std::runtime_error("Database file does not exist.");
  }

  nlohmann::json db;
  std::ifstream ifs(dbpath);
  ifs >> db;
  ifs.close();

  for (const auto &p : db) {
    Patient patient(p["id"], p["name"], GetGenderFromString(p["gender"]), p["age"], p["height"],
                    p["weight"]);
    for (const auto &c : p["cases"]) {
      std::vector<Symptom> symptoms;
      for (const auto &s : c["symptoms"]) {
        symptoms.emplace_back(GetSymptomFromString(s));
      }
      const Prescription p(c["prescription"]["name"], c["prescription"]["potential_disease"],
                           c["prescription"]["medicines"], c["prescription"]["usage"]);
      patient.AddCase(Case(c["time"], symptoms, p));
    }
    patients_.insert({p["id"], patient});
  }
}

void PatientDatabase::SavePatientsJsonFile(std::string dbpath) {
  nlohmann::json db;
  for (const auto &[id, p] : patients_) {
    nlohmann::json patient;
    patient["id"] = p.id();
    patient["name"] = p.name();
    patient["gender"] = GetStringFromGender(p.gender());
    patient["age"] = p.age();
    patient["height"] = p.height();
    patient["weight"] = p.weight();
    patient["cases"] = nlohmann::json::array();
    for (const auto &c : p.cases()) {
      nlohmann::json case_json;
      case_json["time"] = c.case_time();
      for (const auto &s : c.symptoms()) {
        case_json["symptoms"].push_back(GetStringFromSymptom(s));
      }
      case_json["prescription"]["name"] = c.prescription().name();
      case_json["prescription"]["potential_disease"] = c.prescription().potential_disease();
      case_json["prescription"]["medicines"] = c.prescription().medicines();
      case_json["prescription"]["usage"] = c.prescription().usage();
      patient["cases"].push_back(case_json);
    }
    db.push_back(patient);
  }

  std::ofstream ofs(dbpath);
  ofs << db.dump(2);
}
