#pragma once

#include <optional>
#include <string>
#include <vector>

#include "card.hpp"
#include "deck.hpp"

class Game;

class Player {
 public:
  Player(std::weak_ptr<Game> game);
  void AddOnePoint();
  std::shared_ptr<Card> Draw(std::shared_ptr<Deck> deck);
  void Exchange(std::shared_ptr<Player> player);
  virtual std::optional<int> MakeExchangeDecision() = 0;
  virtual std::shared_ptr<Card> Show() = 0;
  bool IsEmptyHand() const;

  void set_name(const std::string &name);
  std::string name() const;
  int points() const;

 protected:
  std::string name_;
  std::vector<std::shared_ptr<Card>> hand_;
  int points_;
  std::weak_ptr<Game> game_;
};
