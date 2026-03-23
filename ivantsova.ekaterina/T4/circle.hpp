#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "shape.hpp"
#include <stdexcept>
#include <cmath>

namespace ivantsova {
  class Circle : public Shape {
  public:
    Circle(const point_t& center, double radius) :
      center_(center), radius_(radius) {
        if (radius<= 0.0) {
          throw std::invalid_argument("Radius must be positive");
        }
      }

      double getArea() const override {
        return M_PI * radius_ * radius_;
      }

      rectangle_t getFrameRect() const override {
        return rectangle_t(center_, radius_ * 2, radius_ * 2);
      }

      void move (const point_t& newPos) override {
        center_ = newPos;
      }

      void move (double dx, double dy) override {
        center_.x += dx;
        center_.y += dy;
      }

      void scale(double coefficient) override {
        if (coefficient <= 0.0) {
          throw std::invalid_argument("coefficient must be positive");
        }
        radius_ *= coefficient;
      }

  private:
    point_t center_;
    double radius_;
  };
}

#endif
