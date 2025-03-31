#pragma once

#include <database.hpp>

class EnvGuardedDatabaseProxy : public Database {
 public:
  EnvGuardedDatabaseProxy();
  std::shared_ptr<Employee> GetEmployeeById(int id) override;

 private:
  std::shared_ptr<Database> database_;
};
