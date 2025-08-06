#include <patient.hpp>
#include <stdexcept>

Patient::Patient(const std::string &id, const std::string &name, Gender gender, int age,
                 double height, double weight)
    : id_(id), name_(name), gender_(gender), age_(age), height_(height), weight_(weight) {
  if (id_.size() != 10 || std::isupper(id_[0]) == 0) {
    throw std::invalid_argument("Invalid patient ID");
  }

  for (int i = 1; i < 10; ++i) {
    if (std::isdigit(id_[i]) == 0) {
      throw std::invalid_argument("Invalid patient ID");
    }
  }

  if (name_.empty() || name_.size() > 30) {
    throw std::invalid_argument("Invalid patient name");
  }

  if (age_ < 1 || age_ > 180) {
    throw std::invalid_argument("Invalid patient age");
  }

  if (height_ < 1 || height_ > 500) {
    throw std::invalid_argument("Invalid patient height");
  }

  if (weight_ < 1 || weight_ > 500) {
    throw std::invalid_argument("Invalid patient weight");
  }
}

void Patient::AddCase(const Case &c) { cases_.emplace_back(c); }
