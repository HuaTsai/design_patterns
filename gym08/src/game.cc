#include <game.hpp>
#include <print>
#include <random>

void Game::Start() {
  map_objects_.resize(kMapSize, std::vector<std::weak_ptr<MapObject>>(kMapSize));

  // Create treasures
  for (int i = 0; i < kTreasuresCount; ++i) {
    auto [x, y] = GetRandomEmptyPosition();
    auto treasure = CreateRandomTreasure(x, y);
    treasures_.push_back(treasure);
    map_objects_[x][y] = treasure;
  }

  // Create monsters
  for (int i = 0; i < kMonstersCount; ++i) {
    auto [x, y] = GetRandomEmptyPosition();
    auto monster = std::make_shared<Monster>(x, y);
    monster->SetDefaultState();
    monsters_.push_back(monster);
    map_objects_[x][y] = monster;
  }

  // Create obstacles
  for (int i = 0; i < kObstaclesCount; ++i) {
    auto [x, y] = GetRandomEmptyPosition();
    auto obstacle = std::make_shared<Obstacle>(x, y);
    obstacles_.push_back(obstacle);
    map_objects_[x][y] = obstacle;
  }

  // Create character
  auto [x, y] = GetRandomEmptyPosition();
  character_ = std::make_shared<Character>(GetRandomDirection(), x, y);
  character_->SetDefaultState();
  map_objects_[x][y] = character_;
}

void Game::RoundStart() {
  DrawMap();
  ShowStatus();

  character_->state()->RoundStartEvent();
  CharacterAction();
  if (dynamic_pointer_cast<AcceleratedState>(character_->state())) {
    DrawMap();
    ShowStatus();
    CharacterAction();
  }

  if (dynamic_pointer_cast<TeleportState>(character_->state())) {
    auto oldrow = character_->row();
    auto oldcol = character_->col();
    auto [newrow, newcol] = GetRandomEmptyPosition();
    character_->set_row(newrow);
    character_->set_col(newcol);
    swap(map_objects_[oldrow][oldcol], map_objects_[newrow][newcol]);
  }

  if (auto trans = character_->state()->RoundEndEvent(); trans) {
    character_->SetState(trans);
  }

  for (auto &monster : monsters_) {
    monster->state()->RoundStartEvent();
    MonsterAction(monster);
    if (std::dynamic_pointer_cast<AcceleratedState>(monster->state())) {
      MonsterAction(monster);
    }

    if (dynamic_pointer_cast<TeleportState>(monster->state())) {
      auto oldrow = monster->row();
      auto oldcol = monster->col();
      auto [newrow, newcol] = GetRandomEmptyPosition();
      monster->set_row(newrow);
      monster->set_col(newcol);
      swap(map_objects_[oldrow][oldcol], map_objects_[newrow][newcol]);
    }

    if (auto trans = monster->state()->RoundEndEvent(); trans) {
      monster->SetState(trans);
    }
  }

  if (character_->hp() == 0) {
    winner_ = "Monsters";
  }

  if (monsters_.empty()) {
    winner_ = "Character";
  }
}

void Game::CharacterAction() {
  if (character_->hp() == 0) {
    return;
  }

  const Options cmd = GetValidCommand();
  int row = character_->row();
  int col = character_->col();

  if (cmd == Options::kAttack) {
    HandleAttackCommand(row, col);
    return;
  }

  ProcessMoveCommand(cmd, row, col);

  if (auto ptr = map_objects_[row][col].lock(); ptr) {
    HandleTreasureInteraction(row, col);
    return;
  }

  ExecuteMovement(cmd);
}

Options Game::GetValidCommand() {
  auto cmd = character_->Action();
  while (true) {
    if (cmd == Options::kInvalid) {
      std::print("\nInvalid action\n");
      cmd = character_->Action();
      continue;
    }

    if ((cmd == Options::kMoveUp && character_->row() == 0) ||
        (cmd == Options::kMoveDown && character_->row() == kMapSize - 1) ||
        (cmd == Options::kMoveLeft && character_->col() == 0) ||
        (cmd == Options::kMoveRight && character_->col() == kMapSize - 1)) {
      std::print("\nBump to the wall!\n");
      cmd = character_->Action();
      continue;
    }

    break;
  }
  return cmd;
}

void Game::HandleAttackCommand(int row, int col) {
  if (dynamic_pointer_cast<EruptingState>(character_->state())) {
    HandleEruptingAttack();
  } else {
    HandleDirectionalAttack(row, col, character_->direction());
  }
}

void Game::HandleEruptingAttack() {
  auto monsters = monsters_;
  for (auto &monster : monsters) {
    character_->Attack(monster);
    if (monster->hp() == 0) {
      std::erase(monsters_, monster);
    }
  }
}

bool Game::IsObstacleAt(int row, int col) {
  return dynamic_pointer_cast<Obstacle>(map_objects_[row][col].lock()) != nullptr;
}

void Game::AttackMonsterAt(int row, int col) {
  if (auto ptr = map_objects_[row][col].lock(); ptr) {
    if (auto monster = dynamic_pointer_cast<Monster>(ptr); monster) {
      character_->Attack(monster);
      if (monster->hp() == 0) {
        std::erase(monsters_, monster);
      }
    }
  }
}

void Game::AttackInDirection(int start_row, int start_col, int delta_row, int delta_col) {
  int row = start_row;
  int col = start_col;

  while (row >= 0 && row < kMapSize && col >= 0 && col < kMapSize) {
    if (IsObstacleAt(row, col)) {
      break;
    }

    AttackMonsterAt(row, col);

    row += delta_row;
    col += delta_col;
  }
}

void Game::HandleDirectionalAttack(int row, int col, Direction dir) {
  switch (dir) {
    using enum Direction;
    case kUp:
      AttackInDirection(row, col, -1, 0);
      break;
    case kDown:
      AttackInDirection(row, col, 1, 0);
      break;
    case kLeft:
      AttackInDirection(row, col, 0, -1);
      break;
    case kRight:
      AttackInDirection(row, col, 0, 1);
      break;
  }
}

void Game::ProcessMoveCommand(Options cmd, int &row, int &col) {
  switch (cmd) {
    using enum Options;
    using enum Direction;
    case kMoveUp:
      --row;
      character_->Turn(kUp);
      break;
    case kMoveDown:
      ++row;
      character_->Turn(kDown);
      break;
    case kMoveLeft:
      --col;
      character_->Turn(kLeft);
      break;
    case kMoveRight:
      ++col;
      character_->Turn(kRight);
      break;
    default:
      break;
  }
}

void Game::HandleTreasureInteraction(int row, int col) {
  if (auto ptr = map_objects_[row][col].lock(); ptr) {
    if (auto treasure = dynamic_pointer_cast<Treasure>(ptr); treasure) {
      character_->state()->SetPendingState(State::CreateStateFromTreasure(treasure, character_));
      std::erase(treasures_, treasure);
    }
  }
}

void Game::ExecuteMovement(Options cmd) {
  if (cmd == Options::kAttack) {
    return;
  }

  map_objects_[character_->row()][character_->col()].reset();
  switch (cmd) {
    using enum Options;
    case kMoveUp:
      character_->Move(Direction::kUp);
      break;
    case kMoveDown:
      character_->Move(Direction::kDown);
      break;
    case kMoveLeft:
      character_->Move(Direction::kLeft);
      break;
    case kMoveRight:
      character_->Move(Direction::kRight);
      break;
    default:
      break;
  }
  map_objects_[character_->row()][character_->col()] = character_;
}

void Game::MonsterAction(const std::shared_ptr<Monster> &monster) {
  if (monster->hp() == 0) {
    return;
  }

  std::vector<int> dirs{0, -1, 0, 1, 0, 0};
  auto isin = [](int x, int y) { return x >= 0 && x < kMapSize && y >= 0 && y < kMapSize; };
  for (int i = 0; i < 4; ++i) {
    const int x = monster->row() + dirs[i];
    const int y = monster->col() + dirs[i + 1];
    if (x == character_->row() && y == character_->col()) {
      monster->Attack(character_);
      return;
    }
  }

  std::uniform_int_distribution<int> dis(0, 4);
  std::default_random_engine dre(std::random_device{}());

  int dir = dis(dre);
  int x = monster->row() + dirs[dir];
  int y = monster->col() + dirs[dir + 1];

  while (!isin(x, y)) {
    dir = dis(dre);
    x = monster->row() + dirs[dir];
    y = monster->col() + dirs[dir + 1];
  }

  if (dir == 4) {
    return;
  }

  auto obj = map_objects_[x][y].lock();

  if (!obj) {
    map_objects_[monster->row()][monster->col()].reset();
    if (dir == 0) {
      monster->Move(Direction::kLeft);
    } else if (dir == 1) {
      monster->Move(Direction::kUp);
    } else if (dir == 2) {
      monster->Move(Direction::kRight);
    } else if (dir == 3) {
      monster->Move(Direction::kDown);
    }
    map_objects_[monster->row()][monster->col()] = monster;
    return;
  }

  if (auto treasure = dynamic_pointer_cast<Treasure>(obj); treasure) {
    monster->state()->SetPendingState(State::CreateStateFromTreasure(treasure, monster));
    std::erase(treasures_, treasure);
  }
}

void Game::DrawMap() const {
  std::print("\x{1b}[2J\x{1b}[1;1H");  // magic code to clear screen
  std::string top("╔");
  for (int i = 0; i < kMapSize * 2 + 1; ++i) {
    top += "═";
  }
  top += "╗";

  std::string bottom("╚");
  for (int i = 0; i < kMapSize * 2 + 1; ++i) {
    bottom += "═";
  }
  bottom += "╝";

  std::print("{}\n", top);
  for (int i = 0; i < kMapSize; ++i) {
    std::print("║ ");
    for (int j = 0; j < kMapSize; ++j) {
      if (auto ptr = map_objects_[i][j].lock(); ptr) {
        std::print("{} ", ptr->symbol());
      } else {
        std::print(". ");
      }
    }
    std::print("║\n");
  }
  std::print("{}\n", bottom);
}

void Game::ShowStatus() const { character_->ShowStatus(); }

std::pair<int, int> Game::GetRandomEmptyPosition() const {
  if (static_cast<int>(treasures_.size() + monsters_.size() + 1) >= kMapSize * kMapSize) {
    throw std::runtime_error("No empty position available");
  }

  std::uniform_int_distribution<int> dis(0, kMapSize - 1);
  std::default_random_engine dre(std::random_device{}());

  while (true) {
    const int i = dis(dre);
    const int j = dis(dre);
    if (!map_objects_[i][j].lock()) {
      return {i, j};
    }
  }
}

bool Game::IsFinish() const { return !winner_.empty(); }

void Game::Finish() {
  DrawMap();
  ShowStatus();
  std::print("Game over! {} wins!\n", winner_);
}
