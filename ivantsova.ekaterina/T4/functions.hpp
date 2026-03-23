#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include "shape.hpp"
#include <vector>
#include <memory>
#include <string>

namespace ivantsova{
  point_t getTopLeftCorner(const rectangle_t& frame);
  void printShape(const std::weak_ptr<Shape>& wshape, const std::string& name, size_t index);
  void printAll(const std::vector<std::weak_ptr<Shape>>& wshapes, const std::vector<std::string>& names);
  rectangle_t getAllFrame(const std::vector<std::weak_ptr<Shape>>& wshapes);
  void printAllFrame(const rectangle_t& rect);
  void scaleShapes(std::vector<std::weak_ptr<Shape>>& wshapes, const point_t& P, double k);
}

#endif
