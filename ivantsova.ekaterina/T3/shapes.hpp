#ifndef SHAPES_HPP
#define SHAPES_HPP

#include <iostream>
#include <vector>

namespace ivantsova {
  struct Point {
    int x, y;
  };

  struct Polygon {
    std::vector< Point > points;
  };

  std::istream& operator>>(std::istream& in, Point& p);
  std::istream& operator>>(std::istream& in, Polygon& p);
  std::ostream& operator<<(std::ostream& out, const Point& p);
  bool operator==(const Point& a, const Point& b);
}

#endif
