#include <prescribe_system.hpp>
#include <print>

int main() {
  PrescribeSystem system("gym10/data/database.json", "gym10/data/support.txt");

  auto pre1 = system.Prescribe("Lily", {Symptom::kSneeze});
  std::print("Lily 的處方是: {}\n", pre1.name());

  auto pre2 = system.Prescribe("Uma", {Symptom::kSneeze, Symptom::kHeadache, Symptom::kCough});
  std::print("Uma 的處方是: {}\n", pre2.name());

  auto pre3 = system.Prescribe("Mason", {Symptom::kSnore});
  std::print("Mason 的處方是: {}\n", pre3.name());

  system.SavePrescriptionToFile("lily.csv", "Lily", pre1);
  system.SavePrescriptionToFile("uma.json", "Uma", pre2);

  const Case case3(3, {Symptom::kSnore}, pre3);
  system.SaveCaseToDatabase("database.json", "Mason", case3);
}
