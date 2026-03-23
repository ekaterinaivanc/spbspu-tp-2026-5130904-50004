#ifndef RING_HPP
#define RING_HPP

#include "shape.hpp"
#include <stdexcept>
#include <cmath>

namespace ivantsova {
  class Ring : public Shape {
  public:
    Ring(const point_t& center, double outRadius, double inRadius) :
      center_(center), outRadius_(outRadius), inRadius_(inRadius) {
        if (outRadius<= 0.0 || inRadius_ <= 0.0) {
          throw std::invalid_argument("Radiuses must be positive");
        }
        if (inRadius_ >= outRadius_) {
          throw std::invalid_argument("Inner radius must be less than outer");
        }
      }

      double getArea() const override {
        return M_PI * (outRadius_ * outRadius_ - inRadius_ * inRadius_);
      }

      rectangle_t getFrameRect() const override {
        return rectangle_t(center_, outRadius_ * 2, outRadius_ * 2);
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
        outRadius_ *= coefficient;
        inRadius_ *= coefficient;
      }

  private:
    point_t center_;
    double outRadius_;
    double inRadius_;
  };
}

#endif
