#include "input_io.hpp"

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
