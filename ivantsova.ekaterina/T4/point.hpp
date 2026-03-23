#ifndef POINT_HPP
#define POINT_HPP

namespace ivantsova {
  struct point_t {
    double x = 0.0;
    double y = 0.0;
    point_t() = default;
    point_t(double x_, double y_) :
      x(x_), y(y_) {}
  };
}

#endif
