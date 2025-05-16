#include <cstring>
#include <env_guarded_database_proxy.hpp>
#include <print>
#include <real_database.hpp>

EnvGuardedDatabaseProxy::EnvGuardedDatabaseProxy() { database_ = std::make_shared<RealDatabase>(); }

// In fish shell, run `set -x PASSWORD=1qaz2wsx`
// In bash shell, run `export PASSWORD=1qaz2wsx`
std::shared_ptr<Employee> EnvGuardedDatabaseProxy::GetEmployeeById(int id) {
  static bool access_granted = false;
  if (!access_granted) {
    const char *password = secure_getenv("PASSWORD");
    if (password == nullptr || std::string(password) != "1qaz2wsx") {
      throw std::runtime_error("Unauthorized access");
    }
    access_granted = true;
    std::println("Access granted");
  }
  return database_->GetEmployeeById(id);
}
