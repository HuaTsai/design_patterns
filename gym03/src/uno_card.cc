#include "uno_card.hpp"

std::string UNOCard::string() const {
  std::string ret;

  switch (color_) {
    using enum Color;
    case kRed:
      ret = "Red";
      break;
    case kYellow:
      ret = "Yellow";
      break;
    case kGreen:
      ret = "Green";
      break;
    case kBlue:
      ret = "Blue";
      break;
    default:
      throw std::runtime_error("Invalid color");
  }

  ret += " ";

  switch (number_) {
    using enum Number;
    case kZero:
      ret += "Zero";
      break;
    case kOne:
      ret += "One";
      break;
    case kTwo:
      ret += "Two";
      break;
    case kThree:
      ret += "Three";
      break;
    case kFour:
      ret += "Four";
      break;
    case kFive:
      ret += "Five";
      break;
    case kSix:
      ret += "Six";
      break;
    case kSeven:
      ret += "Seven";
      break;
    case kEight:
      ret += "Eight";
      break;
    case kNine:
      ret += "Nine";
      break;
    default:
      throw std::runtime_error("Invalid number");
  }

  return ret;
}

bool UNOCard::HasSameColorOrNumber(const UNOCard &other) const {
  return color_ == other.color_ || number_ == other.number_;
}
