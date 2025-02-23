#include "card.hpp"

std::ostream &operator<<(std::ostream &os, std::shared_ptr<Card> card) {
  return os << card->string();
}
