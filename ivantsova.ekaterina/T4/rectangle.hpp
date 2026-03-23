#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"
#include <stdexcept>

namespace ivantsova {
  class Rectangle : public Shape {
  public:
    Rectangle(const point_t& center, double width, double height) :
      center_(center), width_(width), height_(height) {
        if (width_ <= 0.0 || height_ <= 0.0) {
          throw std::invalid_argument("Width and height must be positive");
        }
      }

      double getArea() const override {
        return width_ * height_;
      }

      rectangle_t getFrameRect() const override {
        return rectangle_t(center_, width_, height_);
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
        width_ *= coefficient;
        height_ *= coefficient;
      }

  private:
    point_t center_;
    double width_;
    double height_;
  };
}

#endif
