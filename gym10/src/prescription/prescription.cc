#include <prescription/prescription.hpp>
#include <stdexcept>

Prescription::Prescription(const std::string &name, const std::string &potential_disease,
                           const std::vector<std::string> &medicines, const std::string &usage)
    : name_(std::move(name)),
      potential_disease_(std::move(potential_disease)),
      medicines_(std::move(medicines)),
      usage_(std::move(usage)) {
  if (name_.size() < 4 || name_.size() > 30) {
    throw std::invalid_argument("名字長度應在 4 到 30 之間");
  }

  if (potential_disease_.size() < 3 || potential_disease_.size() > 100) {
    throw std::invalid_argument("疾病名稱長度應在 3 到 100 之間");
  }

  for (const auto &medicine : medicines_) {
    if (medicine.size() < 3 || medicine.size() > 100) {
      throw std::invalid_argument("所有藥品名稱長度應在 3 到 100 之間");
    }
  }

  if (usage_.size() > 1000) {
    throw std::invalid_argument("用法長度應在 1000 以內");
  }
}
