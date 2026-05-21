#include "commands.hpp"
#include "shapes_functions.hpp"
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <functional>
#include <cctype>
#include <string>
#include <limits>

bool evenCount(const ivantsova::Polygon& p) {
  return p.points.size() % 2 == 0;
}

bool oddCount(const ivantsova::Polygon& p) {
  return p.points.size() % 2 == 1;
}

bool countEquals(const ivantsova::Polygon& p, size_t n) {
  return p.points.size() == n;
}

bool areaLess(const ivantsova::Polygon& a, const ivantsova::Polygon& b) {
  return ivantsova::area(a) < ivantsova::area(b);
}

bool vertexLess(const ivantsova::Polygon& a, const ivantsova::Polygon& b) {
  return a.points.size() < b.points.size();
}

bool isDigit(char c) {
  return std::isdigit(c);
}

bool isSpace(char c) {
  return c == ' ';
}

struct SumAll {
  double operator()(double acc, const ivantsova::Polygon& p) const {
    return acc + ivantsova::area(p);
  }
};

struct SumEven {
  double operator()(double acc, const ivantsova::Polygon& p) const {
    return acc + (p.points.size() % 2 == 0 ? ivantsova::area(p) : 0.0);
  }
};

struct SumOdd {
  double operator()(double acc, const ivantsova::Polygon& p) const {
    return acc + (p.points.size() % 2 == 1 ? ivantsova::area(p) : 0.0);
  }
};

struct SumByCount {
  size_t target;
  SumByCount(size_t n) :
    target(n)
  {}
  double operator()(double acc, const ivantsova::Polygon& p) const {
    return acc + (p.points.size() == target ? ivantsova::area(p) : 0.0);
  }
};

void ivantsova::area(std::istream& in, std::ostream& out, const std::vector< Polygon >& polys) {
  std::string param;
  in >> param;
  if (!in) {
    throw std::invalid_argument("invalid");
  }
  out << std::fixed << std::setprecision(1);
  if (param == "MEAN") {
    if (polys.empty()) {
      throw std::invalid_argument("no polygons");
    }
    double total = std::accumulate(polys.begin(), polys.end(), 0.0, SumAll());
    out << total / static_cast< double >(polys.size()) << '\n';
  }
  else if (param == "EVEN") {
    double total = std::accumulate(polys.begin(), polys.end(), 0.0, SumEven());
    out << total << '\n';
  }
  else if (param == "ODD") {
    double total = std::accumulate(polys.begin(), polys.end(), 0.0, SumOdd());
    out << total << '\n';
  }
  else if (std::all_of(param.begin(), param.end(), isDigit)) {
    size_t n = std::stoul(param);
    if (n < 3) {
      throw std::invalid_argument("invalid number of vertex");
    }
    double total = std::accumulate(polys.begin(), polys.end(), 0.0, SumByCount(n));
    out << total << '\n';
  } else {
    throw std::invalid_argument("invalid parameter");
  }
  std::string rest;
  std::getline(in, rest);
  if (!std::all_of(rest.begin(), rest.end(), isSpace)) {
    throw std::invalid_argument("invalid parameter");
  }
}

void ivantsova::max(std::istream& in, std::ostream& out, const std::vector< Polygon >& polys) {
  if (polys.empty()) {
    throw std::invalid_argument("no polygons");
  }
  std::string param;
  in >> param;
  if (!in) {
    throw std::invalid_argument("invalid");
  }
  if (param == "AREA") {
    auto it = std::max_element(polys.begin(), polys.end(), areaLess);
    out << std::fixed << std::setprecision(1) << ivantsova::area(*it) << '\n';
  }
  else if (param == "VERTEXES") {
    auto it = std::max_element(polys.begin(), polys.end(), vertexLess);
    out << it->points.size() << '\n';
  } else {
    throw std::invalid_argument("invalid parameter");
  }
  std::string rest;
  std::getline(in, rest);
  if (!std::all_of(rest.begin(), rest.end(), isSpace)) {
    throw std::invalid_argument("invalid parameter");
  }
}

void ivantsova::min(std::istream& in, std::ostream& out, const std::vector< Polygon >& polys) {
  if (polys.empty()) {
    throw std::invalid_argument("no polygons");
  }
  std::string param;
  in >> param;
  if (!in) {
    throw std::invalid_argument("invalid");
  }
  if (param == "AREA") {
    auto it = std::min_element(polys.begin(), polys.end(), areaLess);
    out << std::fixed << std::setprecision(1) << ivantsova::area(*it) << '\n';
  }
  else if (param == "VERTEXES") {
    auto it = std::min_element(polys.begin(), polys.end(), vertexLess);
    out << it->points.size() << '\n';
  } else {
    throw std::invalid_argument("invalid parameter");
  }
  std::string rest;
  std::getline(in, rest);
  if (!std::all_of(rest.begin(), rest.end(), isSpace)) {
    throw std::invalid_argument("invalid parameter");
  }
}

void ivantsova::count(std::istream& in, std::ostream& out, const std::vector< Polygon >& polys) {
  std::string param;
  in >> param;
  if (!in) {
    throw std::invalid_argument("invalid");
  }
  if (param == "EVEN") {
    out << std::count_if(polys.begin(), polys.end(), evenCount) << '\n';
  }
  else if (param == "ODD") {
    out << std::count_if(polys.begin(), polys.end(), oddCount) << '\n';
  }
  else if (std::all_of(param.begin(), param.end(), isDigit)) {
    size_t n = std::stoul(param);
    if (n < 3) {
      throw std::invalid_argument("invalid nubber of vertex");
    }
    out << std::count_if(polys.begin(), polys.end(), std::bind(countEquals, std::placeholders::_1, n)) << '\n';
  } else {
    throw std::invalid_argument("invalid parameter");
  }
  std::string rest;
  std::getline(in, rest);
  if (!std::all_of(rest.begin(), rest.end(), isSpace)) {
    throw std::invalid_argument("invalid parameter");
  }
}

void ivantsova::rects(std::istream& in, std::ostream& out, const std::vector< Polygon >& polys) {
  std::string rest;
  std::getline(in, rest);
  if (!std::all_of(rest.begin(), rest.end(), isSpace)) {
    throw std::invalid_argument("invalid parameter");
  }
  out << std::count_if(polys.begin(), polys.end(), ivantsova::isRectangle) << '\n';
}

void ivantsova::same(std::istream& in, std::ostream& out, const std::vector< Polygon >& polys) {
  Polygon target;
  if (!(in >> target)) {
    in.clear();
    in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    out << "<INVALID COMMAND>\n";
    return;
  }
  if (target.points.size() < 3) {
    out << "<INVALID COMMAND>\n";
    return;
  }
  std::string rest;
  std::getline(in, rest);
  if (!std::all_of(rest.begin(), rest.end(), isSpace)) {
    out << "<INVALID COMMAND>\n";
    return;
  }
  auto func = std::bind(&ivantsova::isSame, std::placeholders::_1, std::cref(target));
  out << std::count_if(polys.begin(), polys.end(), func) << "\n";
}
