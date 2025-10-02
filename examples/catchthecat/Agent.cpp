#include "Agent.h"
#include <unordered_set>
#include <queue>
#include "World.h"
using namespace std;

//a* target is the edge of the map in both cases
std::vector<Point2D> Agent::generatePath(World* w) { //this is where we do dijkstra's/a* (I kinda want to do a*)
  unordered_map<Point2D, Point2D> cameFrom;  // to build the flowfield and build the path
  queue<Point2D> frontier;                   // to store next ones to visit
  unordered_set<Point2D> frontierSet;        // OPTIMIZATION to check faster if a point is in the queue
  unordered_map<Point2D, bool> visited;      // use .at() to get data, if the element doesn't exist [] will give you wrong results

  // bootstrap state
  auto catPos = w->getCat();
  frontier.push(catPos);
  frontierSet.insert(catPos);
  Point2D borderExit = Point2D::INFINITE;  // if at the end of the loop we don't find a border, we have to return random points
  auto sideSizeOver2 = w->getWorldSideSize() / 2;

  while (!frontier.empty()) {
    // get the current from frontier
    auto current = frontier.front();
    // remove the current from frontierset
    frontier.pop();
    // mark current as visited
    visited.emplace(current, true);
    // getVisitableNeightbors(world, current) returns a vector of neighbors that are not visited, not cat, not block, not in the queue
    std::vector<Point2D> neighbors = getVisitableNeighbors(w, &current, visited);
    // iterate over the neighbors:
    for (Point2D n : neighbors) {
      // for every neighbor set the cameFrom
      cameFrom.emplace(n, current);
      // enqueue the neighbors to frontier and frontierset
      frontier.push(n);
      frontierSet.insert(n);
      // do this up to find a visitable border and break the loop
      if ((n.x == sideSizeOver2) || (n.x == -sideSizeOver2) || (n.y == sideSizeOver2) || (n.y == -sideSizeOver2)) {
        break;
      }
    }
    std::vector<Point2D> path;

    return path;
  }

  // if the border is not infinity, build the path from border to the cat using the camefrom map
  // if there isnt a reachable border, just return empty vector
  // if your vector is filled from the border to the cat, the first element is the catcher move, and the last element is the cat move
  return vector<Point2D>();
}

std::vector<Point2D> Agent::getVisitableNeighbors(World* w, Point2D* p, unordered_map<Point2D, bool> v) {
  std::vector<Point2D> neighbors;
  //ignore the current point, visited points, cat position
  //EAST
  Point2D east = w->E(*p);
  if (!w->isValidPosition(east)) { //is the point on the grid
    if (!v.at(east)) { //has it been visited?
      if (east != w->getCat()) { //is the cat there?
        neighbors.push_back(east);
      }
    }
  }
  //WEST
  Point2D west = w->W(*p);
  if (!w->isValidPosition(west)) { //is the point on the grid
    if (!v.at(west)) { //has it been visited?
      if (west != w->getCat()) { //is the cat there?
        neighbors.push_back(west);
      }
    }
  }
  //NORTHEAST
  Point2D nEast = w->NE(*p);
  if (!w->isValidPosition(nEast)) { //is the point on the grid
    if (!v.at(nEast)) { //has it been visited?
      if (nEast != w->getCat()) { //is the cat there?
        neighbors.push_back(nEast);
      }
    }
  }
  //NORTHWEST
  Point2D nWest = w->NW(*p);
  if (!w->isValidPosition(nWest)) { //is the point on the grid
    if (!v.at(nWest)) { //has it been visited?
      if (nWest != w->getCat()) { //is the cat there?
        neighbors.push_back(nWest);
      }
    }
  }
  //SOUTHEAST
  Point2D sEast = w->SE(*p);
  if (!w->isValidPosition(sEast)) { //is the point on the grid
    if (!v.at(sEast)) { //has it been visited?
      if (sEast != w->getCat()) { //is the cat there?
        neighbors.push_back(sEast);
      }
    }
  }
  //SOUTHWEST
  Point2D sWest = w->SW(*p);
  if (!w->isValidPosition(sWest)) { //is the point on the grid
    if (!v.at(sWest)) { //has it been visited?
      if (sWest != w->getCat()) { //is the cat there?
        neighbors.push_back(sWest);
      }
    }
  }

  return neighbors;
}
