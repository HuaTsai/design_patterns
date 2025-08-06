#include "player.hpp"

Player::Player(std::weak_ptr<Game> game) : points_(0), game_(game) {}

void Player::AddOnePoint() { ++points_; }

std::shared_ptr<Card> Player::Draw(std::shared_ptr<Deck> deck) {
  auto ret = deck->Deal();
  hand_.push_back(ret);
  return ret;
}

void Player::Exchange(std::shared_ptr<Player> player) { hand_.swap(player->hand_); }

bool Player::IsEmptyHand() const { return hand_.empty(); }

void Player::set_name(const std::string &name) { name_ = name; }

std::string Player::name() const { return name_; }

std::vector<std::shared_ptr<Card>> &Player::hand() { return hand_; }

int Player::points() const { return points_; }

std::shared_ptr<Game> Player::game() { return game_.lock(); }
