#include <algorithm>
#include <prescription/attractive_prescription_handler.hpp>

bool AttractivePrescriptionHandler::Match(const Patient &patient,
                                          const std::vector<Symptom> &symptoms) {
  auto sneeze = std::ranges::count_if(
      symptoms, [](const Symptom &symptom) { return symptom == Symptom::kSneeze; });
  return sneeze > 0 && patient.age() == 18 && patient.gender() == Gender::kFemale;
}

Prescription AttractivePrescriptionHandler::PrescribeImpl() {
  return Prescription("青春抑制劑", "有人想你了", {"假鬢角", "臭味"},
                      "把假鬢角黏在臉的兩側，讓自己異性緣差一點，自然就不會有人想妳了。");
}
