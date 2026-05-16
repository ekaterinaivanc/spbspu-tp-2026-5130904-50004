#ifndef INPUT_IO_HPP
#define INPUT_IO_HPP

#include <iostream>
#include <vector>
#include <string>

namespace ivantsova {
  class IOGuard {
  public:
    explicit IOGuard(std::basic_ios< char >& s);
    ~IOGuard();
  private:
    std::basic_ios< char >& s_;
    std::streamsize precision_;
    std::streamsize width_;
    std::basic_ios< char >::fmtflags flags_;
    char fill_;
  };

  struct DoubleSci {
    double value;
  };

  struct UllBin {
    unsigned long long value;
  };
}

#endif
