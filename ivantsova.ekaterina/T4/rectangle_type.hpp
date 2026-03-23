#ifndef RECTANGLE_TYPE_HPP
#define RECTANGLE_TYPE_HPP

#include "point.hpp"

namespace ivantsova {
  struct rectangle_t {
    point_t pos;
    double width = 0.0;
    double height = 0.0;
    rectangle_t() = default;
    rectangle_t(const point_t& pos_, double width_, double height_) :
      pos(pos_), width(width_), height(height_) {}
  };
}

#endif
