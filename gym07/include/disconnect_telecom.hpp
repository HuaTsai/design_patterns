#pragma once

#include <memory>

#include "command.hpp"
#include "telecom.hpp"

class DisconnectTelecom : public Command {
 public:
  explicit DisconnectTelecom(std::shared_ptr<Telecom> telecom);
  void Execute() override;
  void Undo() override;

  std::string name() const override;

 private:
  std::shared_ptr<Telecom> telecom_;
};
