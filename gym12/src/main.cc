#include <env_guarded_database_proxy.hpp>
#include <print>

int main() {
  auto database = std::make_shared<EnvGuardedDatabaseProxy>();

  auto p1 = database->GetEmployeeById(1);
  std::println("ID: {}, Name: {}, Age: {}", p1->id(), p1->name(), p1->age());

  for (const auto &p : p1->GetSubordinates()) {
    std::println("ID: {}, Name: {}, Age: {}", p->id(), p->name(), p->age());
  }

  auto p3 = p1->GetSubordinates()[1];
  for (const auto &p : p3->GetSubordinates()) {
    std::println("ID: {}, Name: {}, Age: {}", p->id(), p->name(), p->age());
  }

  auto p42 = database->GetEmployeeById(42);
  if (!p42) {
    std::println("Employee with ID 42 not found");
  }
}
