#include "Agent.h"
#include <unordered_set>
#include <queue>
#include "World.h"
using namespace std;

struct PrioritizedPoint2D {
  Point2D pos;
  int priority;

  bool operator==(const PrioritizedPoint2D &other) const {
    return pos.x == other.pos.x && pos.y ==other.pos.y;
  }

  bool operator<(const PrioritizedPoint2D &other) const {
    return priority > other.priority;
  }
};

template<>
struct std::hash<PrioritizedPoint2D> {
  size_t operator()(const PrioritizedPoint2D &p) const {
    return hash<int>()(p.pos.x) ^ (hash<int>()(p.pos.y) << 1);
  }
};

int Agent::heuristic(Point2D p, World* w) {
  auto sideSizeOver2 = w->getWorldSideSize() / 2;
  //return sideSizeOver2 - max(abs(p.x), abs(p.y));
  return std::min(sideSizeOver2 - abs(p.x), sideSizeOver2 - abs(p.y));
}

//a* target is the edge of the map in both cases
std::vector<Point2D> Agent::generatePath(World* w) { //this is where we do dijkstra's/a* (I kinda want to do a*)
  unordered_map<Point2D, Point2D> cameFrom;  // to build the flowfield and build the path
  priority_queue<PrioritizedPoint2D> frontier;                   // to store next ones to visit
  unordered_set<Point2D> frontierSet;        // OPTIMIZATION to check faster if a point is in the queue
  visited.clear(); //reset visited

  // bootstrap state
  auto catPos = w->getCat();
  frontier.push({catPos, 0});
  frontierSet.insert(catPos);
  Point2D borderExit = Point2D::INFINITE;  // if at the end of the loop we don't find a border, we have to return random points
  auto sideSizeOver2 = w->getWorldSideSize() / 2;
  std::vector<Point2D> path;

  while (!frontier.empty()) {
    // get the current from frontier
    auto current = frontier.top();
    //check if we're at the end of the map
    if (w->catWinsOnSpace(current.pos)) {
      Point2D p = current.pos;
      while (!w->catCanMoveToPosition(p)) {
        path.push_back(p);
        p = cameFrom[p];
      }
      path.push_back(p);
      return path;
    }

    frontier.pop();
    visited.emplace(current.pos);
    // getVisitableNeightbors(world, current) returns a vector of neighbors that are not visited, not cat, not block, not in the queue
    std::vector<Point2D> neighbors = getVisitableNeighbors(w, &current.pos);
    for (Point2D n : neighbors) { // iterate over the neighbors:
      cameFrom.emplace(n, current.pos); // for every neighbor set the cameFrom
      int priority = heuristic(n, w);
      frontier.push({n, priority}); // enqueue the neighbors to frontier and frontierset
      frontierSet.insert(n);
      // do this up to find a visitable border and break the loop
      if ((n.x == sideSizeOver2) || (n.x == -sideSizeOver2) || (n.y == sideSizeOver2) || (n.y == -sideSizeOver2)) {
        break;
      }
    }
  }
  // if the border is not infinity, build the path from border to the cat using the camefrom map
  // if there isnt a reachable border, just return empty vector
  // if your vector is filled from the border to the cat, the first element is the catcher move, and the last element is the cat move
  return vector<Point2D>();
}

std::vector<Point2D> Agent::getVisitableNeighbors(World* w, Point2D* p) {
  std::vector<Point2D> neighbors;
  //ignore the current point, visited points, cat position
  //EAST
  Point2D east = w->E(*p);
  if (w->isValidPosition(east)) { //is the point on the grid
    if (!visited.contains(east)) { //has it been visited?
      if (east != w->getCat()) { //is the cat there?
        if (!w->getContent(east.x, east.y)) { //is the point blocked?
          neighbors.push_back(east);
        }
      }
    }
  }
  //WEST
  Point2D west = w->W(*p);
  if (w->isValidPosition(west)) { //is the point on the grid
    if (!visited.contains(west)) { //has it been visited?
      if (west != w->getCat()) { //is the cat there?
        if (!w->getContent(west.x, west.y)) {
          neighbors.push_back(west);
        }
      }
    }
  }
  //NORTHEAST
  Point2D nEast = w->NE(*p);
  if (w->isValidPosition(nEast)) { //is the point on the grid
    if (!visited.contains(nEast)) { //has it been visited?
      if (nEast != w->getCat()) { //is the cat there?
        if (!w->getContent(nEast.x, nEast.y)) {
          neighbors.push_back(nEast);
        }
      }
    }
  }
  //NORTHWEST
  Point2D nWest = w->NW(*p);
  if (w->isValidPosition(nWest)) { //is the point on the grid
    if (!visited.contains(nWest)) { //has it been visited?
      if (nWest != w->getCat()) { //is the cat there?
        if (!w->getContent(nWest.x, nWest.y)) {
          neighbors.push_back(nWest);
        }
      }
    }
  }
  //SOUTHEAST
  Point2D sEast = w->SE(*p);
  if (w->isValidPosition(sEast)) { //is the point on the grid
    if (!visited.contains(sEast)) { //has it been visited?
      if (sEast != w->getCat()) { //is the cat there?
        if (!w->getContent(sEast.x, sEast.y)) {
          neighbors.push_back(sEast);
        }
      }
    }
  }
  //SOUTHWEST
  Point2D sWest = w->SW(*p);
  if (w->isValidPosition(sWest)) { //is the point on the grid
    if (!visited.contains(sWest)) { //has it been visited?
      if (sWest != w->getCat()) { //is the cat there?
        if (!w->getContent(sWest.x, sWest.y)) {
          neighbors.push_back(sWest);
        }
      }
    }
  }

  return neighbors;
}

std::vector<Point2D> Agent::getMoveableNeighbors(World* w, Point2D* p) { //not reliant on visted list for a*, for cat and catcher
  std::vector<Point2D> neighbors;
  //EAST
  Point2D east = w->E(*p);
  if (w->isValidPosition(east)) { //is the point on the grid
    if (east != w->getCat()) { //is the cat there?
      if (!w->getContent(east.x, east.y)) { //is the point blocked?
        neighbors.push_back(east);
      }
    }
  }
  //WEST
  Point2D west = w->W(*p);
  if (w->isValidPosition(west)) { //is the point on the grid
    if (west != w->getCat()) { //is the cat there?
      if (!w->getContent(west.x, west.y)) {
        neighbors.push_back(west);
      }
    }
  }
  //NORTHEAST
  Point2D nEast = w->NE(*p);
  if (w->isValidPosition(nEast)) { //is the point on the grid
    if (nEast != w->getCat()) { //is the cat there?
      if (!w->getContent(nEast.x, nEast.y)) {
        neighbors.push_back(nEast);
      }
    }
  }
  //NORTHWEST
  Point2D nWest = w->NW(*p);
  if (w->isValidPosition(nWest)) { //is the point on the grid
    if (nWest != w->getCat()) { //is the cat there?
      if (!w->getContent(nWest.x, nWest.y)) {
        neighbors.push_back(nWest);
      }
    }
  }
  //SOUTHEAST
  Point2D sEast = w->SE(*p);
  if (w->isValidPosition(sEast)) { //is the point on the grid
    if (sEast != w->getCat()) { //is the cat there?
      if (!w->getContent(sEast.x, sEast.y)) {
        neighbors.push_back(sEast);
      }
    }
  }
  //SOUTHWEST
  Point2D sWest = w->SW(*p);
  if (w->isValidPosition(sWest)) { //is the point on the grid
    if (sWest != w->getCat()) { //is the cat there?
      if (!w->getContent(sWest.x, sWest.y)) {
        neighbors.push_back(sWest);
      }
    }
  }

  return neighbors;
}
