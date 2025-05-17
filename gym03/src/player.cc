#include "player.hpp"

Player::Player(Type type) : type_(type), points_(0), topcard_(nullptr) {}

void Player::Draw(std::shared_ptr<Deck> deck) { hand_.push_back(deck->Deal()); }

void Player::UpdateTopCard(std::shared_ptr<Card> card) { topcard_ = card; }

void Player::AddPoint() { ++points_; }

bool Player::IsEmptyHand() const { return hand_.empty(); }

Player::Type Player::type() const { return type_; }

std::string Player::name() const { return name_; }

int Player::points() const { return points_; }

std::shared_ptr<Card> Player::topcard() const { return topcard_; }

std::vector<std::shared_ptr<Card>> Player::hand() const { return hand_; }

std::vector<std::shared_ptr<Card>> &Player::hand() { return hand_; }
