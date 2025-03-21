#pragma once

#include <string>

class MapObject {
 public:
  explicit MapObject(std::string symbol, int row, int col)
      : symbol_(std::move(symbol)), row_(row), col_(col) {}

  virtual ~MapObject() = default;
  MapObject(const MapObject &) = delete;
  MapObject &operator=(const MapObject &) = delete;
  MapObject(MapObject &&) = delete;
  MapObject &operator=(MapObject &&) = delete;

  [[nodiscard]] std::string symbol() const { return symbol_; }
  void set_symbol(std::string symbol) { symbol_ = std::move(symbol); }

  [[nodiscard]] int row() const { return row_; }
  void set_row(int row) { row_ = row; }

  [[nodiscard]] int col() const { return col_; }
  void set_col(int col) { col_ = col; }

 private:
  std::string symbol_;
  int row_;
  int col_;
};
