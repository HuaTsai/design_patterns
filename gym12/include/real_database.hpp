#pragma once

#include <database.hpp>

class RealDatabase : public Database {
 public:
  std::shared_ptr<Employee> GetEmployeeById(int id) override;
};
