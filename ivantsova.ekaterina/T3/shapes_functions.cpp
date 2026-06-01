#include <algorithm>
#include <numeric>
#include <cmath>
#include "shapes_functions.hpp"

double ivantsova::AreaComponent::operator()(size_t i) const
{
  size_t j = (i + 1) % total;
  return static_cast< double >(pts[i].x) * pts[j].y - static_cast< double >(pts[j].x) * pts[i].y;
}

bool ivantsova::AngleCheck::operator()(size_t i) const
{
  size_t prev = (i + 3) % 4;
  size_t next = (i + 1) % 4;
  int dx1 = pts[i].x - pts[prev].x;
  int dy1 = pts[i].y - pts[prev].y;
  int dx2 = pts[next].x - pts[i].x;
  int dy2 = pts[next].y - pts[i].y;
  return dx1 * dx2 + dy1 * dy2 == 0;
}

double ivantsova::area(const ivantsova::Polygon& p)
{
  if (p.points.size() < 3) {
    return 0.0;
  }
  size_t n = p.points.size();
  std::vector< size_t > indices(n);
  std::iota(indices.begin(), indices.end(), 0);
  std::vector< double > components(n);
  std::transform(indices.begin(), indices.end(), components.begin(), AreaComponent{p.points, n});
  double sum = std::accumulate(components.begin(), components.end(), 0.0);
  return std::abs(sum) / 2.0;
}

bool ivantsova::isRectangle(const ivantsova::Polygon& p)
{
  if (p.points.size() != 4) {
    return false;
  }
  std::vector< size_t > indices(4);
  std::iota(indices.begin(), indices.end(), 0);
  return std::all_of(indices.begin(), indices.end(), AngleCheck{p.points});
}

bool ivantsova::isSame(const ivantsova::Polygon& a, const ivantsova::Polygon& b)
{
  return a == b;
}
