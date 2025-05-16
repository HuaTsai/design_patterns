#pragma once

#include <optional>
#include <string>
#include <vector>

#include "card.hpp"
#include "deck.hpp"

class Game;

class Player {
 public:
  explicit Player(std::weak_ptr<Game> game);

  virtual ~Player() = default;
  Player(const Player &) = delete;
  Player &operator=(const Player &) = delete;
  Player(Player &&) = delete;
  Player &operator=(Player &&) = delete;

  void AddOnePoint();
  std::shared_ptr<Card> Draw(std::shared_ptr<Deck> deck);
  void Exchange(std::shared_ptr<Player> player);
  virtual std::optional<int> MakeExchangeDecision() = 0;
  virtual std::shared_ptr<Card> Show() = 0;
  bool IsEmptyHand() const;

  void set_name(const std::string &name);
  std::string name() const;
  std::vector<std::shared_ptr<Card>> &hand();
  int points() const;
  std::shared_ptr<Game> game();

 private:
  std::string name_;
  std::vector<std::shared_ptr<Card>> hand_;
  int points_;
  std::weak_ptr<Game> game_;
};
