#pragma once

#include <employee.hpp>

class Database : public std::enable_shared_from_this<Database> {
 public:
  Database() = default;

  virtual ~Database() = default;
  Database(const Database &) = delete;
  Database &operator=(const Database &) = delete;
  Database(Database &&) = delete;
  Database &operator=(Database &&) = delete;

  virtual std::shared_ptr<Employee> GetEmployeeById(int id) = 0;
};
