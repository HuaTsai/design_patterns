#include <map_object.hpp>

class Obstacle : public MapObject {
 public:
  explicit Obstacle(int row, int col) : MapObject("□", row, col) {}
};
