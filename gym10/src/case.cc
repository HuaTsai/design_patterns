#include <case.hpp>

Case::Case(int case_time, const std::vector<Symptom>& symptoms, const Prescription& prescription)
    : case_time_(case_time), symptoms_(symptoms), prescription_(prescription) {}
