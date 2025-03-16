#include <prescription/covid19_prescription_handler.hpp>

bool Covid19PrescriptionHandler::Match(const Patient & /* patient */,
                                       const std::vector<Symptom> &symptoms) {
  bool sneeze = false;
  bool headache = false;
  bool cough = false;
  for (const auto &symptom : symptoms) {
    if (symptom == Symptom::kSneeze) {
      sneeze = true;
    } else if (symptom == Symptom::kHeadache) {
      headache = true;
    } else if (symptom == Symptom::kCough) {
      cough = true;
    }
  }
  return sneeze && headache && cough;
}

Prescription Covid19PrescriptionHandler::PrescribeImpl() {
  return Prescription("清冠一號", "新冠肺炎", {"清冠一號"},
                      "將相關藥材裝入茶包裡，使用500 mL 溫、熱水沖泡悶煮1~3 分鐘後即可飲用。");
}
