#include "input_io.hpp"
#include <iomanip>
#include <cmath>
#include <limits>

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

std::istream& ivantsova::operator>>(std::istream& is, ivantsova::DoubleSci& ds) {
  std::istream::sentry s(is);
  if (!s) {
    return is;
  }
  ivantsova::IOGuard guard(is);
  double mantissa_int = 0, mantissa_frac = 0;
  char dot = 0, e_char = 0, sign = 0;
  int exponent = 0;

  is >> mantissa_int >> dot >> mantissa_frac >> e_char >> sign >> exponent;
  if (is && dot == '.' && (e_char == 'e' || e_char == 'E')) {
    int frac_digits = 1;
    double temp = mantissa_frac;
    while (temp >= 10) {
      temp /= 10;
      frac_digits++;
    }
    double mantissa = mantissa_int + mantissa_frac / std::pow(10.0, frac_digits);
    ds.value = mantissa * std::pow(10.0, (sign == '-' ? -exponent : exponent));
  } else {
    is.setstate(std::ios_base::failbit);
  }
  return is;
}

std::ostream& ivantsova::operator<<(std::ostream& os, const ivantsova::DoubleSci& ds) {
  ivantsova::IOGuard guard(os);
  os << std::scientific << std::nouppercase << std::setprecision(1) << ds.value;
  return os;
}

bool ivantsova::operator<(const ivantsova::DoubleSci& lhs, const ivantsova::DoubleSci& rhs) {
  return lhs.value < rhs.value;
}

bool ivantsova::operator==(const ivantsova::DoubleSci& lhs, const ivantsova::DoubleSci& rhs) {
  return std::abs(lhs.value - rhs.value) < std::numeric_limits< double >::epsilon();
}
