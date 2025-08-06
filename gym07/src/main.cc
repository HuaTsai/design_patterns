#include <format>
#include <iostream>
#include <print>
#include <sstream>
#include <utility>

#include "connect_telecom.hpp"
#include "disconnect_telecom.hpp"
#include "keyboard.hpp"
#include "move_tank_backward.hpp"
#include "move_tank_forward.hpp"

namespace {
struct Cmd {
  std::string name;
  std::shared_ptr<Command> cmd;
};

void BindSingleCommandInstruction(const std::vector<Cmd> &cmds,
                                  std::shared_ptr<Keyboard> keyboard) {
  std::print("Key: ");
  std::string c;
  std::cin >> c;
  if (c.size() != 1 || (std::isalpha(c[0]) == 0)) {
    throw std::invalid_argument("不合法的指令");
  }

  std::print("要將哪一道指令設置到快捷鍵 {} 上:\n", c[0]);
  for (size_t i = 0; i < cmds.size(); ++i) {
    std::print("({}) {}\n", i, cmds[i].name);
  }

  int cmd = 0;
  std::cin >> cmd;
  if (cmd < 0 || std::cmp_greater_equal(cmd, cmds.size())) {
    throw std::invalid_argument("不合法的指令");
  }

  keyboard->BindOperation(c[0], {cmds[cmd].cmd});
}

void BindMacroCommandInstruction(const std::vector<Cmd> &cmds, std::shared_ptr<Keyboard> keyboard) {
  std::print("Key: ");
  std::string c;
  std::cin >> c;
  if (c.size() != 1 || (std::isalpha(c[0]) == 0)) {
    throw std::invalid_argument("不合法的指令");
  }
  std::cin.ignore();  // skip the newline character

  std::print("要將哪些指令設置成快捷鍵 {} 的巨集（輸入多個數字，以空白隔開）:\n", c[0]);
  for (size_t i = 0; i < cmds.size(); ++i) {
    std::print("({}) {}\n", i, cmds[i].name);
  }

  std::string cmdstr;
  std::getline(std::cin, cmdstr);
  std::stringstream ss(cmdstr);
  std::vector<std::shared_ptr<Command>> macro;
  int cmd = 0;
  while (ss >> cmd) {
    macro.push_back(cmds[cmd].cmd);
  }
  keyboard->BindOperation(c[0], macro);
}
}  // namespace

int main() {
  auto tank = std::make_shared<Tank>();
  auto telecom = std::make_shared<Telecom>();
  const std::shared_ptr<Command> cmd_mtf = std::make_shared<MoveTankForward>(tank);
  const std::shared_ptr<Command> cmd_mtb = std::make_shared<MoveTankBackward>(tank);
  const std::shared_ptr<Command> cmd_ct = std::make_shared<ConnectTelecom>(telecom);
  const std::shared_ptr<Command> cmd_dt = std::make_shared<DisconnectTelecom>(telecom);
  const std::shared_ptr<Command> cmd_reset = nullptr;
  auto keyboard = std::make_shared<Keyboard>();

  std::vector<Cmd> cmds;
  cmds.push_back(Cmd{.name = cmd_mtf->name(), .cmd = cmd_mtf});
  cmds.push_back(Cmd{.name = cmd_mtb->name(), .cmd = cmd_mtb});
  cmds.push_back(Cmd{.name = cmd_ct->name(), .cmd = cmd_ct});
  cmds.push_back(Cmd{.name = cmd_dt->name(), .cmd = cmd_dt});
  cmds.push_back(Cmd{.name = "ResetMainControlKeyboard", .cmd = cmd_reset});

  while (true) {
    std::string cmd;
    std::print("(1) 快捷鍵設置 (2) Undo (3) Redo (字母) 按下按鍵: ");
    std::cin >> cmd;
    if (std::cin.eof()) {
      std::print("Bye\n");
      break;
    }
    if (cmd.size() != 1) {
      throw std::invalid_argument("不合法的指令");
    }
    if (cmd[0] == '1') {
      char set_macro = 0;
      std::print("設置巨集指令 (y/n): ");
      std::cin >> set_macro;
      if (std::tolower(set_macro) == 'y') {
        BindMacroCommandInstruction(cmds, keyboard);
      } else if (std::tolower(set_macro) == 'n') {
        BindSingleCommandInstruction(cmds, keyboard);
      } else {
        throw std::invalid_argument("不合法的指令");
      }
    } else if (cmd[0] == '2') {
      keyboard->Undo();
    } else if (cmd[0] == '3') {
      keyboard->Redo();
    } else if (std::isalpha(cmd[0]) != 0) {
      keyboard->Press(cmd[0]);
    } else {
      throw std::invalid_argument("不合法的指令");
    }
    keyboard->PrintKeymap();
  }
}
