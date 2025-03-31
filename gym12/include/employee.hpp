#pragma once

#include <memory>
#include <string>
#include <vector>

class Database;

class Employee {
 public:
  explicit Employee(int id, const std::string &name, int age,
                    const std::vector<int> &subordinate_ids, std::weak_ptr<Database> database)
      : id_(id), name_(name), age_(age), subordinate_ids_(subordinate_ids), database_(database) {}

  virtual ~Employee() = default;
  Employee(const Employee &) = default;
  Employee &operator=(const Employee &) = default;
  Employee(Employee &&) = default;
  Employee &operator=(Employee &&) = default;

  virtual std::vector<std::shared_ptr<Employee>> &GetSubordinates() { return subordinates_; }

  virtual int id() const { return id_; }
  virtual const std::string &name() const { return name_; }
  virtual int age() const { return age_; }
  virtual const std::vector<int> &subordinate_ids() const { return subordinate_ids_; }
  virtual std::shared_ptr<Database> database() const { return database_.lock(); }

 private:
  int id_;
  std::string name_;
  int age_;
  std::vector<int> subordinate_ids_;
  std::vector<std::shared_ptr<Employee>> subordinates_;
  std::weak_ptr<Database> database_;
};
