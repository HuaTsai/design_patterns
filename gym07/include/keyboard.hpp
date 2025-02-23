#pragma once

#include <memory>
#include <stack>
#include <unordered_map>
#include <vector>

#include "command.hpp"

class Keyboard {
 public:
  void Press(char key);
  void BindOperation(char key, std::vector<std::shared_ptr<Command>> cmds);
  void Undo();
  void Redo();
  void PrintKeymap() const;

 private:
  std::unordered_map<char, std::vector<std::shared_ptr<Command>>> keymap_;
  std::stack<std::unordered_map<char, std::vector<std::shared_ptr<Command>>>> keymap_history_;
  std::stack<std::vector<std::shared_ptr<Command>>> undo_history_;
  std::stack<std::vector<std::shared_ptr<Command>>> redo_history_;
};
