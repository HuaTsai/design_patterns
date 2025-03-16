#pragma once

#include <stdexcept>
#include <string>

enum class Symptom { kSneeze, kHeadache, kCough, kSnore };

inline Symptom GetSymptomFromString(std::string str) {
  if (str == "Sneeze") {
    return Symptom::kSneeze;
  }

  if (str == "Headache") {
    return Symptom::kHeadache;
  }

  if (str == "Cough") {
    return Symptom::kCough;
  }

  if (str == "Snore") {
    return Symptom::kSnore;
  }

  throw std::runtime_error("Invalid symptom " + str);
}

inline std::string GetStringFromSymptom(Symptom s) {
  switch (s) {
    case Symptom::kSneeze:
      return "Sneeze";
    case Symptom::kHeadache:
      return "Headache";
    case Symptom::kCough:
      return "Cough";
    case Symptom::kSnore:
      return "Snore";
    default:
      throw std::runtime_error("Invalid symptom");
  }
}
