#pragma once

#include <prescription/prescription_handler.hpp>

class Covid19PrescriptionHandler : public PrescriptionHandler {
 public:
  using PrescriptionHandler::PrescriptionHandler;
  bool Match(const Patient &patient, const std::vector<Symptom> &symptoms) override;
  Prescription PrescribeImpl() override;
};
