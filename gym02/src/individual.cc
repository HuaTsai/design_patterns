#include "individual.hpp"

#include <algorithm>
#include <iostream>
#include <ranges>
#include <stdexcept>

namespace {
std::string trim(const std::string &s) {
  constexpr const char *whitespace = " \t\n\r\f\v";
  const auto first{s.find_first_not_of(whitespace)};
  if (first == std::string::npos) return {};
  const auto last{s.find_last_not_of(whitespace)};
  return s.substr(first, last - first + 1);
};
}  // namespace

Individual::Individual(int id, Gender gender, int age, const std::string &intro,
                       const std::string &habits, const Coord &coord)
    : gender_(gender), coord_(coord) {
  if (id <= 0) {
    throw std::invalid_argument("id should be positive");
  }
  id_ = id;

  if (age < 18) {
    throw std::invalid_argument("age should be at least 18");
  }
  age_ = age;

  if (intro.size() > 200) {
    throw std::invalid_argument("intro should be less than 200 characters");
  }
  intro_ = intro;

  auto split_view =
      std::ranges::views::split(habits, ',') | std::ranges::views::transform([](auto &&word_view) {
        auto word = trim(std::string(word_view.begin(), word_view.end()));
        if (word.size() < 1 || word.size() > 10) {
          throw std::invalid_argument("habit should be between 1 to 10 characters");
        }
        return word;
      });

  for (const auto &habit : split_view) {
    habits_.push_back(habit);
  }
  std::ranges::sort(habits_);  // for std::ranges::set_intersection later
}

std::string Individual::string() const {
  std::string ret;
  ret += std::format("- id: {}\n", id_);
  ret += std::format("- gender: {}\n", (gender_ == Gender::kMale) ? "Male" : "Female");
  ret += std::format("- age: {}\n", age_);
  ret += std::format("- intro: {}\n", intro_);
  ret += "- habits: ";
  for (size_t i = 0; i < habits_.size(); i++) {
    ret += std::format("{}{}", habits_[i], (i + 1 == habits_.size()) ? "" : ", ");
  }
  ret += std::format("\n- coord: ({}, {})\n", coord_.x, coord_.y);
  return ret;
}

int Individual::id() const { return id_; }

std::vector<std::string> Individual::habits() const { return habits_; }

Coord Individual::coord() const { return coord_; }

std::ostream &operator<<(std::ostream &os, const Individual &individual) {
  os << individual.string();
  return os;
}
