#include <termios.h>
#include <unistd.h>

#include <character.hpp>
#include <iostream>

namespace {
char getkey() {
  struct termios oldt;  // NOLINT
  struct termios newt;  // NOLINT
  char ch = 0;
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(static_cast<unsigned>(ICANON | ECHO));
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  ch = static_cast<char>(getchar());
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  return ch;
}
}  // namespace

Options Character::ActionNormal() {
  std::cout << "Input your action (\"↑\", \"↓\", \"←\", \"→\", \"a\") ";
  char ch = getkey();

  if (ch == '\033') {
    ch = getkey();
    if (ch == '[') {
      ch = getkey();
      switch (ch) {
        case 'A':
          return Options::kMoveUp;
        case 'B':
          return Options::kMoveDown;
        case 'D':
          return Options::kMoveLeft;
        case 'C':
          return Options::kMoveRight;
        default:
          break;
      }
    }
  } else if (ch == 'a' || ch == 'A') {
    return Options::kAttack;
  }

  return Options::kInvalid;
}

Options Character::ActionLeftRight() {
  std::cout << "Input your action (\"←\", \"→\") ";
  char ch = getkey();

  if (ch == '\033') {
    ch = getkey();
    if (ch == '[') {
      ch = getkey();
      switch (ch) {
        case 'D':
          return Options::kMoveLeft;
        case 'C':
          return Options::kMoveRight;
        default:
          break;
      }
    }
  }

  return Options::kInvalid;
}

Options Character::ActionUpDown() {
  std::cout << "Input your action (\"↑\", \"↓\") ";
  char ch = getkey();

  if (ch == '\033') {
    ch = getkey();
    if (ch == '[') {
      ch = getkey();
      switch (ch) {
        case 'A':
          return Options::kMoveUp;
        case 'B':
          return Options::kMoveDown;
        default:
          break;
      }
    }
  }

  return Options::kInvalid;
}

Character::Character(Direction dir, int row, int col)
    : Role(GetDirectionSymbol(dir), row, col, kMaxHp, kPower), direction_(dir) {}

Options Character::Action() {
  if (dynamic_pointer_cast<OrderlessState>(state())) {
    std::uniform_int_distribution<int> dis(0, 1);
    std::default_random_engine dre(std::random_device{}());
    if (dis(dre) == 0) {
      return ActionLeftRight();
    }
    return ActionUpDown();
  }
  return ActionNormal();
}

void Character::ShowStatus() const {
  std::cout << "State: " << state()->name();
  if (state()->remaining_turns() > 0) {
    std::cout << " (" << state()->remaining_turns() << ")";
  }
  std::cout << " | HP: " << hp() << "\n";
}

void Character::Turn(Direction dir) {
  set_symbol(GetDirectionSymbol(dir));
  direction_ = dir;
}
