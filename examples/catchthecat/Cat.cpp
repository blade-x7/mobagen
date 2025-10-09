#include "Cat.h"
#include "World.h"
#include <stdexcept>

Point2D Cat::Move(World* world) {
  std::vector<Point2D> path = generatePath(world);

  if (!path.empty()) { //check if the path is empty
    Point2D newPos;
    newPos = path.at(path.size() - 1);
    return newPos;
  }
  else {
    Point2D currPos = world->getCat();
    std::vector<Point2D> neighbors = getMoveableNeighbors(world, &currPos);
    if (neighbors.empty()) {
      return currPos;
    }
    else {
      auto rand = Random::Range(0, neighbors.size() - 1);
      return neighbors.at(rand);
    }
  }
}