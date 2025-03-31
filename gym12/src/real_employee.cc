#include <database.hpp>
#include <real_employee.hpp>

RealEmployee::RealEmployee(int id, const std::string &name, int age,
                           const std::vector<int> &subordinate_ids, std::weak_ptr<Database> db)
    : Employee(id, name, age, subordinate_ids, db) {
  for (auto id : subordinate_ids) {
    if (auto employee = database()->GetEmployeeById(id); employee) {
      Employee::GetSubordinates().emplace_back(employee);
    }
  }
}

std::vector<std::shared_ptr<Employee>> &RealEmployee::GetSubordinates() {
  return Employee::GetSubordinates();
}
