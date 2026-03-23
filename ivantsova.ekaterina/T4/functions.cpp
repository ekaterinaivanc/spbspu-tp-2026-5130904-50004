#include "functions.hpp"
#include <iostream>
#include <stdexcept>
#include <limits>

ivantsova::point_t ivantsova::getTopLeftCorner(const ivantsova::rectangle_t& frame) {
  double halfW = frame.width / 2.0;
  double halfH = frame.height / 2.0;
  return ivantsova::point_t(frame.pos.x - halfW, frame.pos.y + halfH);
}

void ivantsova::printShape(const std::weak_ptr<ivantsova::Shape>& wptr, const std::string& name, size_t index) {
  auto shape = wptr.lock();
  if (!shape) {
    throw std::runtime_error("Weak pointer expired");
  }
  ivantsova::rectangle_t frame = shape->getFrameRect();
  std::cout << index << "." << name << "\n";
  std::cout << "area = " << shape->getArea() << "\n";
  std::cout << "framerect: center(" << frame.pos.x << ";" << frame.pos.y << "), width = " << frame.width << \
  ", height = " << frame.height << "\n";
}

void ivantsova::printAll(const std::vector<std::weak_ptr<ivantsova::Shape>>& wshapes, const std::vector<std::string>& names) {
  double total = 0.0;
  for (size_t i = 0; i < wshapes.size(); ++i) {
    auto shape = wshapes[i].lock();
    if (shape) {
      ivantsova::printShape(wshapes[i], names[i], i + 1);
      total += shape->getArea();
    }
  }
  std::cout << "Total area = " << total << "\n";
}

ivantsova::rectangle_t ivantsova::getAllFrame(const std::vector<std::weak_ptr<ivantsova::Shape>>& wshapes) {
  if (wshapes.empty()) {
    return ivantsova::rectangle_t(ivantsova::point_t(0.0, 0.0), 0.0, 0.0);
  }
  double minX = std::numeric_limits<double>::max();
  double minY = std::numeric_limits<double>::max();
  double maxX = std::numeric_limits<double>::lowest();
  double maxY = std::numeric_limits<double>::lowest();
  for (const auto& wptr : wshapes) {
    auto shape = wptr.lock();
    if (!shape) {
      continue;
    }
    ivantsova::rectangle_t frame = shape->getFrameRect();
    double halfW = frame.width / 2.0;
    double halfH = frame.height / 2.0;
    double left = frame.pos.x - halfW;
    double right = frame.pos.x + halfW;
    double bottom = frame.pos.y - halfH;
    double top = frame.pos.y + halfH;
    if (left < minX) {
      minX = left;
    }
    if (right > maxX) {
      maxX = right;
    }
    if (bottom < minY) {
      minY = bottom;
    }
    if (top > maxY) {
      maxY = top;
    }
  }
  double width = maxX - minX;
  double height = maxY - minY;
  ivantsova::point_t center = {(minX + maxX) / 2.0, (minY + maxY) / 2.0};
  return ivantsova::rectangle_t(center, width, height);
}

void ivantsova::printAllFrame(const ivantsova::rectangle_t& rect) {
  std::cout << "Total framerect: center: (" << rect.pos.x << ";" << rect.pos.y << ")" << "\n";
  std::cout << "width = " << rect.width << ", height = " << rect.height << "\n";
}

void ivantsova::scaleShapes(std::vector<std::weak_ptr<ivantsova::Shape>>& wshapes, const ivantsova::point_t& P, double k) {
  for (const auto& wptr : wshapes) {
    auto shape = wptr.lock();
    if (!shape) {
      continue;
    }
    ivantsova::rectangle_t frame = shape->getFrameRect();
    ivantsova::point_t C = frame.pos;
    ivantsova::point_t A = ivantsova::getTopLeftCorner(frame);
    shape->move(P.x - A.x, P.y - A.y);
    shape->scale(k);
    frame = shape->getFrameRect();
    ivantsova::point_t C_mid = frame.pos;
    ivantsova::point_t A_cur;
    A_cur.x = C_mid.x + (A.x - C.x) * k;
    A_cur.y = C_mid.y + (A.y - C.y) * k;
    ivantsova::point_t A_res;
    A_res.x = P.x + (A.x - P.x) * k;
    A_res.y = P.y + (A.y - P.y) * k;
    shape->move(A_res.x - A_cur.x, A_res.y - A_cur.y);
  }
}
