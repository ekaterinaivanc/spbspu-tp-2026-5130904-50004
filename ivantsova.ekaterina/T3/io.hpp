#ifndef IO_HPP
#define IO_HPP

#include <iostream>
#include <vector>
#include "shapes.hpp"

namespace ivantsova {
  struct DelimIO
  {
    char expected;
  };
  std::istream& operator>>(std::istream& in, DelimIO&& delim);

  struct IOGuard
  {
    explicit IOGuard(std::basic_ios< char >& s);
    ~IOGuard();
  private:
    std::basic_ios< char >& s_;
    std::streamsize precision_;
    std::streamsize width_;
    std::ios_base::fmtflags flags_;
    char fill_;
  };

  void readData(std::istream& is, std::vector< Polygon >& polys);
}

#endif
