#include "Agent.h"
#include <unordered_set>
#include <unordered_map>
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

  while (!frontier.empty()) {
    // get the current from frontier
    auto current = frontier.front();
    // remove the current from frontierset
    frontier.pop();
    // mark current as visited
    visited.emplace(current, true);
    // getVisitableNeightbors(world, current) returns a vector of neighbors that are not visited, not cat, not block, not in the queue
    std::vector<Point2D> neighbors = getVisitableNeighbors(w, &current);
    // iterate over the neighs:
    for (Point2D n : neighbors) {
      // for every neighbor set the cameFrom
      // enqueue the neighbors to frontier and frontierset
      // do this up to find a visitable border and break the loop
    }
  }

  // if the border is not infinity, build the path from border to the cat using the camefrom map
  // if there isnt a reachable border, just return empty vector
  // if your vector is filled from the border to the cat, the first element is the catcher move, and the last element is the cat move
  return vector<Point2D>();
}

std::vector<Point2D> Agent::getVisitableNeighbors(World* w, Point2D* p) {
  std::vector<Point2D> neighbors;

  //how does this work for hex grid

  return neighbors;
}
