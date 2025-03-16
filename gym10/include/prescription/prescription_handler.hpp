#pragma once

#include <memory>
#include <patient.hpp>
#include <prescription/prescription.hpp>
#include <symptom.hpp>

class PrescriptionHandler {
 public:
  explicit PrescriptionHandler(std::shared_ptr<PrescriptionHandler> next);

  virtual ~PrescriptionHandler() = default;
  PrescriptionHandler(const PrescriptionHandler &) = delete;
  PrescriptionHandler &operator=(const PrescriptionHandler &) = delete;
  PrescriptionHandler(PrescriptionHandler &&) = delete;
  PrescriptionHandler &operator=(PrescriptionHandler &&) = delete;

  Prescription Prescribe(const Patient &patient, const std::vector<Symptom> &symptoms);
  virtual bool Match(const Patient &patient, const std::vector<Symptom> &symptoms) = 0;
  virtual Prescription PrescribeImpl() = 0;

 private:
  std::shared_ptr<PrescriptionHandler> next_;
};
