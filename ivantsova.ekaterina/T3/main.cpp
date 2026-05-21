#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <functional>
#include <string>
#include <limits>
#include "commands.hpp"
#include "shapes.hpp"
#include "io.hpp"

int main(int argc, char** argv) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <file>\n";
    return 1;
  }
  std::ifstream file(argv[1]);
  if (!file) {
    std::cerr << "Cannot open file\n";
    return 1;
  }

  std::vector< ivantsova::Polygon > polygons;
  ivantsova::readData(file, polygons);

  std::map< std::string, std::function< void() > > cmd;
  cmd["AREA"] = std::bind(ivantsova::area, std::ref(std::cin), std::ref(std::cout), std::cref(polygons));
  cmd["MAX"] = std::bind(ivantsova::max, std::ref(std::cin), std::ref(std::cout), std::cref(polygons));
  cmd["MIN"] = std::bind(ivantsova::min, std::ref(std::cin), std::ref(std::cout), std::cref(polygons));
  cmd["COUNT"] = std::bind(ivantsova::count, std::ref(std::cin), std::ref(std::cout), std::cref(polygons));
  cmd["RECTS"] = std::bind(ivantsova::rects, std::ref(std::cin), std::ref(std::cout), std::cref(polygons));
  cmd["SAME"] = std::bind(ivantsova::same, std::ref(std::cin), std::ref(std::cout), std::cref(polygons));

  std::string command;
  while (std::cin >> command) {
    try {
      cmd.at(command)();
    } catch (...) {
      if (std::cin.fail()) {
        std::cin.clear();
      }
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
      std::cout << "<INVALID COMMAND>\n";
    }
  }
  return 0;
}
