#ifndef AGENT_H
#define AGENT_H
#include "math/Point2D.h"
#include <vector>
#include <unordered_map>
#include <unordered_set>

class World;

class Agent {
private:
  std::unordered_set<Point2D> visited;
public:
  explicit Agent() = default;

  virtual Point2D Move(World*) = 0;

  std::vector<Point2D> generatePath(World* w);
  std::vector<Point2D> getVisitableNeighbors(World* w, Point2D* p);
  std::vector<Point2D> getMoveableNeighbors(World* w, Point2D* p);
  int heuristic(Point2D p, World* w);
};

#endif  // AGENT_H
