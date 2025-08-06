#pragma once

#include <character.hpp>
#include <map_object.hpp>
#include <memory>
#include <monster.hpp>
#include <obstacle.hpp>
#include <treasure.hpp>
#include <vector>

class Game {
  static constexpr int kMapSize = 10;
  static constexpr int kTreasuresCount = 10;
  static constexpr int kMonstersCount = 5;
  static constexpr int kObstaclesCount = 10;

 public:
  void Start();
  void RoundStart();
  void extracted();
  void CharacterAction();
  void MonsterAction(const std::shared_ptr<Monster> &monster);
  [[nodiscard]] bool IsFinish() const;
  void Finish();

  [[nodiscard]] std::string winner() const;

 private:
  void DrawMap() const;
  void ShowStatus() const;
  [[nodiscard]] std::pair<int, int> GetRandomEmptyPosition() const;

  Options GetValidCommand();
  void HandleAttackCommand(int row, int col);
  void HandleEruptingAttack();
  void HandleDirectionalAttack(int row, int col, Direction dir);
  bool IsObstacleAt(int row, int col);
  void AttackMonsterAt(int row, int col);
  void AttackInDirection(int start_row, int start_col, int delta_row, int delta_col);
  void ProcessMoveCommand(Options cmd, int &row, int &col);
  void HandleTreasureInteraction(int row, int col);
  void ExecuteMovement(Options cmd);

  std::vector<std::vector<std::weak_ptr<MapObject>>> map_objects_;
  std::vector<std::shared_ptr<Treasure>> treasures_;
  std::vector<std::shared_ptr<Monster>> monsters_;
  std::vector<std::shared_ptr<Obstacle>> obstacles_;
  std::shared_ptr<Character> character_;
  std::string winner_;
};
