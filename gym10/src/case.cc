#include <case.hpp>

Case::Case(int case_time, std::vector<Symptom> symptoms, Prescription prescription)
    : case_time_(case_time), symptoms_(std::move(symptoms)), prescription_(prescription) {}
