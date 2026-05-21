#include "shapes.hpp"
#include "io.hpp"
#include <algorithm>
#include <iterator>
#include <numeric>

bool ivantsova::operator==(const ivantsova::Point& a, const ivantsova::Point& b) {
  return a.x == b.x && a.y == b.y;
}

std::istream& ivantsova::operator>>(std::istream& in, ivantsova::Point& p) {
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  ivantsova::Point temp{0, 0};
  in >> DelimIO{'('} >> temp.x >> DelimIO{';'} >> temp.y >> DelimIO{')'};
  if (in) {
    p = temp;
  }
  return in;
}

std::ostream& ivantsova::operator<<(std::ostream& out, const ivantsova::Point& p) {
  out << '(' << p.x << ';' << p.y << ')';
  return out;
}

std::istream& ivantsova::operator>>(std::istream& in, ivantsova::Polygon& p) {
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  IOGuard guard(in);
  size_t count = 0;
  if (!(in >> count) || count < 3) {
    in.setstate(std::ios::failbit);
    return in;
  }
  std::vector< ivantsova::Point > pts;
  pts.reserve(count);
  std::copy_n(std::istream_iterator< ivantsova::Point >(in), count, std::back_inserter(pts));
  if (in) {
    p.points = std::move(pts);
  }
  return in;
}
