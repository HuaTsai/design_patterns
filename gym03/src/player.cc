#include "player.hpp"

Player::Player(Type type) : type_(type), points_(0), topcard_(nullptr) {}

void Player::Draw(std::shared_ptr<Deck> deck) { hand_.push_back(deck->Deal()); }

void Player::UpdateTopCard(std::shared_ptr<Card> card) { topcard_ = card; }

void Player::AddPoint() { ++points_; }

bool Player::IsEmptyHand() const { return hand_.empty(); }

std::string Player::name() const { return name_; }

int Player::points() const { return points_; }
