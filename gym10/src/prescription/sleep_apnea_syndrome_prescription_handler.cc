#include <algorithm>
#include <prescription/sleep_apnea_syndrome_prescription_handler.hpp>

bool SleepApneaSyndromePrescriptionHandler::Match(const Patient &patient,
                                                  const std::vector<Symptom> &symptoms) {
  auto snore = std::ranges::count_if(
      symptoms, [](const Symptom &symptom) { return symptom == Symptom::kSnore; });
  const double bmi = patient.weight() / ((patient.height() / 100.) * (patient.height() / 100.));
  return snore > 0 && bmi > 26;
}

Prescription SleepApneaSyndromePrescriptionHandler::PrescribeImpl() {
  return Prescription("打呼抑制劑", "睡眠呼吸中止症", {"一捲膠帶"},
                      "睡覺時，撕下兩塊膠帶，將兩塊膠帶交錯黏在關閉的嘴巴上，就不會打呼了。");
}
