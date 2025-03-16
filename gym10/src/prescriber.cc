#include <filesystem>
#include <fstream>
#include <prescriber.hpp>
#include <print>
#include <thread>

// Concrete prescriptions
#include <prescription/attractive_prescription_handler.hpp>
#include <prescription/covid19_prescription_handler.hpp>
#include <prescription/sleep_apnea_syndrome_prescription_handler.hpp>

Prescriber::Prescriber() : prescription_handler_(nullptr) {}

Prescription Prescriber::Prescribe(const Patient &patient, std::vector<Symptom> symptoms) {
  std::println("Prescribing {}...", patient.name());
  std::this_thread::sleep_for(std::chrono::seconds(3));
  return prescription_handler_->Prescribe(patient, symptoms);
}

void Prescriber::LoadSupportedPotentialDiseases(std::string filepath) {
  if (!std::filesystem::exists(filepath)) {
    throw std::runtime_error("File not found: " + filepath);
  }

  std::ifstream ifs(filepath);
  std::string support;
  while (ifs >> support) {
    std::string support_lower;
    std::ranges::transform(support, std::back_inserter(support_lower), ::tolower);
    if (support_lower == "covid19") {
      prescription_handler_ = std::make_shared<Covid19PrescriptionHandler>(prescription_handler_);
    } else if (support_lower == "attractive") {
      prescription_handler_ =
          std::make_shared<AttractivePrescriptionHandler>(prescription_handler_);
    } else if (support_lower == "sleepapneasyndrome") {
      prescription_handler_ =
          std::make_shared<SleepApneaSyndromePrescriptionHandler>(prescription_handler_);
    } else {
      throw std::runtime_error("Unsupported potential disease: " + support);
    }
  }
}
