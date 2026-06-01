#include "io.hpp"
#include "shapes.hpp"

std::istream& ivantsova::operator>>(std::istream& in, ivantsova::DelimIO&& delim)
{
  char c = 0;
  in >> c;
  if (!in) {
    return in;
  }
  if (c != delim.expected) {
    in.setstate(std::ios::failbit);
  }
  return in;
}

ivantsova::IOGuard::IOGuard(std::basic_ios< char >& s):
 s_(s),
 precision_(s.precision()),
 width_(s.width()),
 flags_(s.flags()),
 fill_(s.fill())
{}

ivantsova::IOGuard::~IOGuard()
{
  s_.precision(precision_);
  s_.width(width_);
  s_.flags(flags_);
  s_.fill(fill_);
}

void ivantsova::readData(std::istream& is, std::vector< Polygon >& polys)
{
  if (is.eof()) {
    return;
  }
  Polygon p;
  if (is >> p) {
    polys.push_back(p);
    readData(is, polys);
    return;
  }
  if (is.eof()) {
    return;
  }
  is.clear();
  std::string trash;
  if (is >> trash) {
    readData(is, polys);
  }
}
