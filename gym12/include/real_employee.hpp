#pragma once

#include <employee.hpp>

class RealEmployee : public Employee {
 public:
  RealEmployee(int id, const std::string &name, int age, const std::vector<int> &subordinate_ids,
               std::weak_ptr<Database> db);
  std::vector<std::shared_ptr<Employee>> &GetSubordinates() override;
};
