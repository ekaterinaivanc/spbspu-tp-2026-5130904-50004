#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iostream>
#include <vector>
#include "shapes.hpp"

namespace ivantsova {
  void area(std::istream& in, std::ostream& out, const std::vector< Polygon >& polys);
  void max(std::istream& in, std::ostream& out, const std::vector< Polygon >& polys);
  void min(std::istream& in, std::ostream& out, const std::vector< Polygon >& polys);
  void count(std::istream& in, std::ostream& out, const std::vector< Polygon >& polys);
  void rects(std::istream& in, std::ostream& out, const std::vector< Polygon >& polys);
  void same(std::istream& in, std::ostream& out, const std::vector< Polygon >& polys);
}

#endif
