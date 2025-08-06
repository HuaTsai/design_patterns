#pragma once

#include <format>
#include <string>
#include <vector>

struct Coord {
  int x;
  int y;
};

enum class Gender { kMale, kFemale };

class Individual {
 public:
  explicit Individual(int id, Gender gender, int age, const std::string &intro,
                      const std::string &habits, const Coord &coord);
  std::string string() const;

  int id() const;
  std::vector<std::string> habits() const;
  Coord coord() const;

 private:
  int id_;
  Gender gender_;
  int age_;
  std::string intro_;
  std::vector<std::string> habits_;
  Coord coord_;
};

template <>
struct std::formatter<Individual> : formatter<string> {
  template <typename FormatContext>
  auto format(const Individual &individual, FormatContext &ctx) const {
    return format_to(ctx.out(), "{}", individual.string());
  }
};

std::ostream &operator<<(std::ostream &os, const Individual &individual);
