#include "Catcher.h"
#include "World.h"

Point2D Catcher::Move(World* world) {
  std::vector<Point2D> path = generatePath(world);
  Point2D nextMove;

  if (!path.empty()) {
    nextMove = path.at(0);
    return nextMove;
  }
  else {
    Point2D catPos = world->getCat();
    std::vector<Point2D> catNeighbors = getMoveableNeighbors(world, &catPos);
    if (catNeighbors.empty()) {
      return nextMove;
    }
    else {
      auto rand = Random::Range(0, catNeighbors.size() - 1);
      return catNeighbors.at(rand);
    }
  }
}
