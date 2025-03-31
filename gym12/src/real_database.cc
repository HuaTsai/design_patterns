#include <fstream>
#include <real_database.hpp>
#include <real_employee.hpp>
#include <sstream>
#include <virtual_employee_proxy.hpp>

std::shared_ptr<Employee> RealDatabase::GetEmployeeById(int id) {
  std::ifstream ifs("../data/database.txt");
  if (!ifs) {
    throw std::runtime_error("Failed to open database file");
  }

  for (int i = 0; i < id; ++i) {
    std::string skip;
    if (!std::getline(ifs, skip)) {
      return nullptr;
    }
  }

  std::string line;
  if (!std::getline(ifs, line)) {
    return nullptr;
  }
  ifs.close();

  std::istringstream ss(line);
  int idx = 0;
  std::string name;
  int age = 0;
  std::vector<int> subordinates;
  ss >> idx >> name >> age;

  if (id != idx) {
    throw std::runtime_error("ID mismatch");
  }

  std::string idstr;
  if (ss >> idstr) {
    std::istringstream idss(idstr);
    std::string id;
    while (std::getline(idss, id, ',')) {
      subordinates.emplace_back(std::stoi(id));
    }
  }

  // Use RealEmployee, all subordinates will be loaded (DFS)
  // return std::make_shared<RealEmployee>(id, name, age, subordinates, shared_from_this());

  // We can also use a proxy for the lazy loading
  return std::make_shared<VirtualEmployeeProxy>(id, name, age, subordinates, shared_from_this());
}
