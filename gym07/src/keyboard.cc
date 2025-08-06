#include "keyboard.hpp"

#include <iostream>
#include <print>
#include <ranges>

void Keyboard::Press(char key) {
  if (!keymap_.contains(key)) {
    return;
  }
  bool reset_key = false;
  for (const auto &cmd : keymap_[key]) {
    if (cmd) {
      cmd->Execute();
    } else {
      reset_key = true;
    }
  }
  undo_history_.push(keymap_[key]);
  redo_history_ = std::stack<std::vector<std::shared_ptr<Command>>>();
  if (reset_key) {
    keymap_history_.push(keymap_);
    keymap_.clear();
  }
}

void Keyboard::BindOperation(char key, std::vector<std::shared_ptr<Command>> cmds) {
  keymap_[key] = cmds;
}

void Keyboard::Undo() {
  if (undo_history_.empty()) {
    return;
  }
  auto cmds = undo_history_.top();
  undo_history_.pop();
  bool reset_key = false;
  for (const auto &cmd : cmds | std::views::reverse) {
    if (cmd) {
      cmd->Undo();
    } else {
      reset_key = true;
    }
  }
  redo_history_.push(cmds);
  if (reset_key) {
    keymap_ = keymap_history_.top();
    keymap_history_.pop();
  }
}

void Keyboard::Redo() {
  if (redo_history_.empty()) {
    return;
  }
  auto cmds = redo_history_.top();
  redo_history_.pop();
  bool reset_key = false;
  for (const auto &cmd : cmds) {
    if (cmd) {
      cmd->Execute();
    } else {
      reset_key = true;
    }
  }
  undo_history_.push(cmds);
  if (reset_key) {
    keymap_history_.push(keymap_);
    keymap_.clear();
  }
}

void Keyboard::PrintKeymap() const {
  for (const auto &[key, cmds] : keymap_) {
    std::print("{}: ", key);
    for (const auto &cmd : cmds) {
      if (cmd) {
        std::print("{} ", cmd->name());
      } else {
        std::print("ResetMainControlKeyboard ");
      }
    }
    std::print("\n");
  }
}
