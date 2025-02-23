#include "uno_card.hpp"

std::string UNOCard::string() const {
  std::string ret;

  switch (color_) {
    case Color::kRed:
      ret = "Red";
      break;
    case Color::kYellow:
      ret = "Yellow";
      break;
    case Color::kGreen:
      ret = "Green";
      break;
    case Color::kBlue:
      ret = "Blue";
      break;
    default:
      throw std::runtime_error("Invalid color");
      break;
  }

  ret += " ";

  switch (number_) {
    case Number::kZero:
      ret += "Zero";
      break;
    case Number::kOne:
      ret += "One";
      break;
    case Number::kTwo:
      ret += "Two";
      break;
    case Number::kThree:
      ret += "Three";
      break;
    case Number::kFour:
      ret += "Four";
      break;
    case Number::kFive:
      ret += "Five";
      break;
    case Number::kSix:
      ret += "Six";
      break;
    case Number::kSeven:
      ret += "Seven";
      break;
    case Number::kEight:
      ret += "Eight";
      break;
    case Number::kNine:
      ret += "Nine";
      break;
    default:
      throw std::runtime_error("Invalid number");
      break;
  }

  return ret;
}

bool UNOCard::HasSameColorOrNumber(const UNOCard &other) const {
  return color_ == other.color_ || number_ == other.number_;
}
