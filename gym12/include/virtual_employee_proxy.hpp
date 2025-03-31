#pragma once

#include <employee.hpp>

class VirtualEmployeeProxy : public Employee {
 public:
  VirtualEmployeeProxy(int id, const std::string &name, int age,
                       const std::vector<int> &subordinate_ids, std::weak_ptr<Database> db);
  std::vector<std::shared_ptr<Employee>> &GetSubordinates() override;

  int id() const override;
  const std::string &name() const override;
  int age() const override;
  const std::vector<int> &subordinate_ids() const override;
  std::shared_ptr<Database> database() const override;

 private:
  std::shared_ptr<Employee> employee_;
};
