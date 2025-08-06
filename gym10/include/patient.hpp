#pragma once

#include <algorithm>
#include <case.hpp>
#include <string>

enum class Gender { kMale, kFemale };

inline Gender GetGenderFromString(const std::string &str) {
  std::string str_lower;
  std::ranges::transform(str, std::back_inserter(str_lower), ::tolower);

  if (str_lower == "male") {
    return Gender::kMale;
  }

  if (str_lower == "female") {
    return Gender::kFemale;
  }

  throw std::runtime_error("Invalid gender " + str);
}

inline std::string GetStringFromGender(const Gender &gender) {
  return gender == Gender::kMale ? "Male" : "Female";
}

class Patient {
 public:
  Patient(const std::string &id, const std::string &name, Gender gender, int age, double height,
          double weight);

  void AddCase(const Case &c);

  const std::string &id() const { return id_; }
  const std::string &name() const { return name_; }
  Gender gender() const { return gender_; }
  int age() const { return age_; }
  double height() const { return height_; }
  double weight() const { return weight_; }
  const std::vector<Case> &cases() const { return cases_; }

 private:
  std::string id_;
  std::string name_;
  Gender gender_;
  int age_;
  double height_;
  double weight_;
  std::vector<Case> cases_;
};
