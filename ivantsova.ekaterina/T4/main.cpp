#include "shape.hpp"
#include "rectangle.hpp"
#include "circle.hpp"
#include "ring.hpp"
#include "functions.hpp"

#include <string>
#include <vector>
#include <iostream>

int main()
{
  try {
    std::vector<std::shared_ptr<ivantsova::Shape>> shapes;
    std::vector<std::string> names;
    shapes.push_back(std::make_shared<ivantsova::Rectangle>(ivantsova::point_t(0.0, 0.0), 4.0, 2.0));
    names.push_back("Rectangle");

    shapes.push_back(std::make_shared<ivantsova::Circle>(ivantsova::point_t(3.0, 2.0), 1.5));
    names.push_back("Circle");

    shapes.push_back(std::make_shared<ivantsova::Ring>(ivantsova::point_t(-2.0, 1.0), 3.0, 1.5));
    names.push_back("Ring");

    std::vector<std::weak_ptr<ivantsova::Shape>> wshapes;
    for (const auto& shape : shapes) {
      wshapes.push_back(shape);
    }
    std::cout << "Before" << "\n";
    ivantsova::printAll(wshapes, names);
    ivantsova::printAllFrame(ivantsova::getAllFrame(wshapes));
    double x, y, k;
    if (!(std::cin>> x >> y)) {
      return 0;
    }
    if (!(std::cin >> k)) {
      std::cerr << "invalid input" << "\n";
      return 1;
    }
    ivantsova::scaleShapes(wshapes, ivantsova::point_t(x, y), k);
    std::cout << "After" << "\n";
    ivantsova::printAll(wshapes, names);
    ivantsova::printAllFrame(ivantsova::getAllFrame(wshapes));
  } catch (const std::exception& e) {
    std::cerr << e.what() << "\n";
    return 1;
  }
  return 0;
}
