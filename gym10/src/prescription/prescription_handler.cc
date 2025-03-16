#include <prescription/prescription_handler.hpp>

PrescriptionHandler::PrescriptionHandler(std::shared_ptr<PrescriptionHandler> next) : next_(next) {}

Prescription PrescriptionHandler::Prescribe(const Patient &patient,
                                            const std::vector<Symptom> &symptoms) {
  if (Match(patient, symptoms)) {
    return PrescribeImpl();
  }

  if (next_) {
    return next_->Prescribe(patient, symptoms);
  }

  throw std::runtime_error("No prescription found.");
}
