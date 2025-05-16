#include <game.hpp>
#include <iostream>
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

  auto cmd = character_->Action();
  while (true) {
    if (cmd == Options::kInvalid) {
      std::cout << "\nInvalid action\n";
      cmd = character_->Action();
      continue;
    }

    if ((cmd == Options::kMoveUp && character_->row() == 0) ||
        (cmd == Options::kMoveDown && character_->row() == kMapSize - 1) ||
        (cmd == Options::kMoveLeft && character_->col() == 0) ||
        (cmd == Options::kMoveRight && character_->col() == kMapSize - 1)) {
      std::cout << "\nBump to the wall!\n";
      cmd = character_->Action();
      continue;
    }

    break;
  }

  int row = character_->row();
  int col = character_->col();

  if (cmd == Options::kAttack) {
    if (dynamic_pointer_cast<EruptingState>(character_->state())) {
      auto monsters = monsters_;
      for (auto &monster : monsters) {
        character_->Attack(monster);
        if (monster->hp() == 0) {
          std::erase(monsters_, monster);
        }
      }
    } else if (character_->direction() == Direction::kUp) {
      for (int i = row; i >= 0; --i) {
        if (auto ptr = dynamic_pointer_cast<Obstacle>(map_objects_[i][col].lock()); ptr) {
          break;
        }
        if (auto ptr = map_objects_[i][col].lock(); ptr) {
          if (auto monster = dynamic_pointer_cast<Monster>(ptr); monster) {
            character_->Attack(monster);
            if (monster->hp() == 0) {
              std::erase(monsters_, monster);
            }
          }
        }
      }
    } else if (character_->direction() == Direction::kDown) {
      for (int i = row; i < kMapSize; ++i) {
        if (auto ptr = dynamic_pointer_cast<Obstacle>(map_objects_[i][col].lock()); ptr) {
          break;
        }
        if (auto ptr = map_objects_[i][col].lock(); ptr) {
          if (auto monster = dynamic_pointer_cast<Monster>(ptr); monster) {
            character_->Attack(monster);
            if (monster->hp() == 0) {
              std::erase(monsters_, monster);
            }
          }
        }
      }
    } else if (character_->direction() == Direction::kLeft) {
      for (int j = col; j >= 0; --j) {
        if (auto ptr = dynamic_pointer_cast<Obstacle>(map_objects_[row][j].lock()); ptr) {
          break;
        }
        if (auto ptr = map_objects_[row][j].lock(); ptr) {
          if (auto monster = dynamic_pointer_cast<Monster>(ptr); monster) {
            character_->Attack(monster);
            if (monster->hp() == 0) {
              std::erase(monsters_, monster);
            }
          }
        }
      }
    } else if (character_->direction() == Direction::kRight) {
      for (int j = col; j < kMapSize; ++j) {
        if (auto ptr = dynamic_pointer_cast<Obstacle>(map_objects_[row][j].lock()); ptr) {
          break;
        }
        if (auto ptr = map_objects_[row][j].lock(); ptr) {
          if (auto monster = dynamic_pointer_cast<Monster>(ptr); monster) {
            character_->Attack(monster);
            if (monster->hp() == 0) {
              std::erase(monsters_, monster);
            }
          }
        }
      }
    }
    return;
  }

  if (cmd == Options::kMoveUp) {
    --row;
    character_->Turn(Direction::kUp);
  } else if (cmd == Options::kMoveDown) {
    ++row;
    character_->Turn(Direction::kDown);
  } else if (cmd == Options::kMoveLeft) {
    --col;
    character_->Turn(Direction::kLeft);
  } else if (cmd == Options::kMoveRight) {
    ++col;
    character_->Turn(Direction::kRight);
  }

  if (auto ptr = map_objects_[row][col].lock(); ptr) {
    if (auto treasure = dynamic_pointer_cast<Treasure>(ptr); treasure) {
      character_->state()->SetPendingState(State::CreateStateFromTreasure(treasure, character_));
      std::erase(treasures_, treasure);
    }
    return;
  }

  map_objects_[character_->row()][character_->col()].reset();
  if (cmd == Options::kMoveUp) {
    character_->Move(Direction::kUp);
  } else if (cmd == Options::kMoveDown) {
    character_->Move(Direction::kDown);
  } else if (cmd == Options::kMoveLeft) {
    character_->Move(Direction::kLeft);
  } else if (cmd == Options::kMoveRight) {
    character_->Move(Direction::kRight);
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
    int x = monster->row() + dirs[i];
    int y = monster->col() + dirs[i + 1];
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
  std::cout << "\033[2J\033[1;1H";  // magic code to clear screen
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

  std::cout << top << "\n";
  for (int i = 0; i < kMapSize; ++i) {
    std::cout << "║ ";
    for (int j = 0; j < kMapSize; ++j) {
      if (auto ptr = map_objects_[i][j].lock(); ptr) {
        std::cout << ptr->symbol().c_str() << " ";
      } else {
        std::cout << ". ";
      }
    }
    std::cout << "║\n";
  }
  std::cout << bottom << "\n";
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
  std::cout << "Game over! " << winner_ << " wins!\n";
}
