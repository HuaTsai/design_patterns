#pragma once

#include <memory>

#include "command.hpp"
#include "tank.hpp"

class MoveTankForward : public Command {
 public:
  explicit MoveTankForward(std::shared_ptr<Tank> tank);
  void Execute() override;
  void Undo() override;

  std::string name() const override;

 private:
  std::shared_ptr<Tank> tank_;
};
