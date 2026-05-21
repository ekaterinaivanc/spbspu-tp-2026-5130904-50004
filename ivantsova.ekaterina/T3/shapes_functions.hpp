#ifndef SHAPES_FUNCTIONS_HPP
#define SHAPES_FUNCTIONS_HPP

#include "shapes.hpp"

namespace ivantsova {
  double area(const Polygon& p);
  bool isRectangle(const Polygon& p);
  bool isSame(const Polygon& a, const Polygon& b);

  struct AreaComponent {
    const std::vector< Point >& pts;
    size_t total;
    double operator()(size_t i) const;
  };

  struct AngleCheck {
    const std::vector< Point >& pts;
    bool operator()(size_t i) const;
  };
}

#endif
