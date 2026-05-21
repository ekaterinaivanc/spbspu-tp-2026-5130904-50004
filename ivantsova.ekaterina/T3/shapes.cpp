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
  if (in && pts.size() == count) {
    p.points = std::move(pts);
  } else {
    in.setstate(std::ios::failbit);
  }
  return in;
}

struct ShiftToOrigin {
  const ivantsova::Point& base;
  ivantsova::Point operator()(const ivantsova::Point& p) const {
    return ivantsova::Point{p.x - base.x, p.y - base.y};
  }
};

struct CompareWithOffset {
  const std::vector< ivantsova::Point >& first;
  const std::vector< ivantsova::Point >& second;
  size_t offset;
  CompareWithOffset(const std::vector< ivantsova::Point >& a, const std::vector< ivantsova::Point >& b, size_t off) :
    first(a),
    second(b),
    offset(off)
  {}
  bool operator()(size_t idx) const {
    return first[idx] == second[(offset + idx) % second.size()];
  }
};

struct IsTrue {
  bool operator()(bool v) const {
    return v;
  }
};

struct CheckOffset {
  const std::vector< ivantsova::Point >& normA;
  const std::vector< ivantsova::Point >& normB;
  const std::vector< size_t >& indices;
  CheckOffset(const std::vector<ivantsova::Point>& a, const std::vector<ivantsova::Point>& b, const std::vector<size_t>& idx) :
    normA(a),
    normB(b),
    indices(idx)
  {}
  bool operator()(size_t start) const {
    std::vector< bool > matches(indices.size());
    std::transform(indices.begin(), indices.end(), matches.begin(), CompareWithOffset(normA, normB, start));
    return std::all_of(matches.begin(), matches.end(), IsTrue());
  }
};

bool ivantsova::operator==(const ivantsova::Polygon& a, const ivantsova::Polygon& b) {
  if (a.points.size() != b.points.size()) {
    return false;
  }
  if (a.points.empty()) {
    return true;
  }
  size_t n = a.points.size();
  ShiftToOrigin shiftA{a.points.front()};
  ShiftToOrigin shiftB{b.points.front()};

  std::vector< ivantsova::Point > normA(n), normB(n);
  std::transform(a.points.begin(), a.points.end(), normA.begin(), shiftA);
  std::transform(b.points.begin(), b.points.end(), normB.begin(), shiftB);

  std::vector< size_t > indices(n);
  std::iota(indices.begin(), indices.end(), 0);

  std::vector< bool > results(n);
  std::transform(indices.begin(), indices.end(), results.begin(), CheckOffset(normA, normB, indices));
  return std::any_of(results.begin(), results.end(), IsTrue());
}
