#include "io.hpp"

std::istream& ivantsova::operator>>(std::istream& in, ivantsova::DelimIO&& delim) {
  char c;
  in >> c;
  if (c != delim.expected) {
    in.setstate(std::ios::failbit);
  }
  return in;
}

ivantsova::IOGuard::IOGuard(std::basic_ios< char >& s) :
  s_(s),
  precision_(s.precision()),
  width_(s.width()),
  flags_(s.flags()),
  fill_(s.fill())
{}

ivantsova::IOGuard::~IOGuard() {
  s_.precision(precision_);
  s_.width(width_);
  s_.flags(flags_);
  s_.fill(fill_);
}
