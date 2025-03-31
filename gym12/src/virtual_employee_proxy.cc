#include <database.hpp>
#include <real_employee.hpp>
#include <virtual_employee_proxy.hpp>

VirtualEmployeeProxy::VirtualEmployeeProxy(int id, const std::string &name, int age,
                                           const std::vector<int> &subordinate_ids,
                                           std::weak_ptr<Database> db)
    : Employee(id, name, age, subordinate_ids, db), employee_(nullptr) {
  // Key difference: we do not load subordinates here
}

std::vector<std::shared_ptr<Employee>> &VirtualEmployeeProxy::GetSubordinates() {
  if (!employee_) {
    employee_ = std::make_shared<RealEmployee>(id(), name(), age(), subordinate_ids(), database());
  }
  return employee_->GetSubordinates();
}

// Delegation of properties:
// GetSubordinates() is the method that loads the RealEmployee
// Before loading the RealEmployee, we return the values from the proxy
// After loading the RealEmployee, we return the values from RealEmployee
int VirtualEmployeeProxy::id() const {
  if (employee_) {
    return employee_->id();
  }
  return Employee::id();
}

const std::string &VirtualEmployeeProxy::name() const {
  if (employee_) {
    return employee_->name();
  }
  return Employee::name();
}

int VirtualEmployeeProxy::age() const {
  if (employee_) {
    return employee_->age();
  }
  return Employee::age();
}

const std::vector<int> &VirtualEmployeeProxy::subordinate_ids() const {
  if (employee_) {
    return employee_->subordinate_ids();
  }
  return Employee::subordinate_ids();
}

std::shared_ptr<Database> VirtualEmployeeProxy::database() const {
  if (employee_) {
    return employee_->database();
  }
  return Employee::database();
}
