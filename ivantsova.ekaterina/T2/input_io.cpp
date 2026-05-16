#include "input_io.hpp"
#include "data_struct.hpp"
#include <iomanip>
#include <cmath>
#include <limits>
#include <vector>
#include <sstream>

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
  std::string token;
  char c;
  while (is.get(c)) {
    if (c == ' ' || c == '\t' || c == '\n' || c == ':' || c == ')') {
      is.unget();
      break;
    }
    token += c;
  }
  bool hasExponent = false;
  for (char ch : token) {
    if (ch == 'e' || ch == 'E') {
      hasExponent = true;
      break;
    }
  }
  if (!hasExponent) {
    is.setstate(std::ios_base::failbit);
    return is;
  }
  std::stringstream ss(token);
  ss >> ds.value;
  if (ss.fail()) is.setstate(std::ios_base::failbit);
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

std::istream& ivantsova::operator>>(std::istream& is, ivantsova::UllBin& ub) {
  std::istream::sentry s(is);
  if (!s) {
    return is;
  }
  ivantsova::IOGuard guard(is);
  std::string token;
  char c;
  while (is.get(c)) {
    if (c == ' ' || c == '\t' || c == '\n' || c == ':' || c == ')') {
      is.unget();
      break;
    }
    token += c;
  }
  if (token.empty()) {
    is.setstate(std::ios_base::failbit);
    return is;
  }
  if (token.size() >= 3 && token[0] == '0' && (token[1] == 'b' || token[1] == 'B')) {
    ub.value = 0;
    for (size_t i = 2; i < token.size(); ++i) {
      if (token[i] != '0' && token[i] != '1') {
        is.setstate(std::ios_base::failbit);
        return is;
      }
      ub.value = (ub.value << 1) | (token[i] - '0');
    }
  } else {
    try {
      size_t processed_chars = 0;
      ub.value = std::stoull(token, &processed_chars);
    } catch (...) {
      is.setstate(std::ios_base::failbit);
    }
  }
  return is;
}

std::ostream& ivantsova::operator<<(std::ostream& os, const ivantsova::UllBin& ub) {
  ivantsova::IOGuard guard(os);
  os << "0b";
  if (ub.value == 0) {
    os << '0';
    return os;
  }
  std::string bin;
  unsigned long long n = ub.value;
  while (n > 0) {
    bin = char('0' + (n & 1)) + bin;
    n >>= 1;
  }
  os << bin;
  return os;
}

bool ivantsova::operator<(const ivantsova::UllBin& lhs, const ivantsova::UllBin& rhs) {
  return lhs.value < rhs.value;
}

bool ivantsova::operator==(const ivantsova::UllBin& lhs, const ivantsova::UllBin& rhs) {
  return lhs.value == rhs.value;
}

char ivantsova::check(std::istream& is, char expected) {
  char c = 0;
  is >> c;
  if (c != expected) {
    is.setstate(std::ios_base::failbit);
  }
  return c;
}

std::istream& ivantsova::operator>>(std::istream& is, ivantsova::DelimeterIO del) {
  del.last = ivantsova::check(is, del.expected);
  return is;
}

static std::istream& getValueByKey(std::istream& is, std::string key, std::vector< bool >& is_been, ivantsova::DataStruct& ds) {
  if (key == "key1") {
    if (is_been[0]) {
        is.setstate(std::ios_base::failbit);
        return is;
    }
    is >> ds.key1;
    is_been[0] = true;
  } else if (key == "key2") {
    if (is_been[1]) {
        is.setstate(std::ios_base::failbit);
        return is;
    }
    is >> ds.key2;
    is_been[1] = true;
  } else if (key == "key3") {
    if (is_been[2]) {
        is.setstate(std::ios_base::failbit);
        return is;
    }
    char quote = 0;
    std::getline(is >> ivantsova::DelimeterIO{'"', quote}, ds.key3, '"');
    is_been[2] = true;
  } else {
    is.setstate(std::ios_base::failbit);
  }
  return is;
}

std::istream& ivantsova::operator>>(std::istream& is, ivantsova::KeyValueIO inp) {
  return getValueByKey(is, inp.key, inp.is_been, inp.ds);
}
