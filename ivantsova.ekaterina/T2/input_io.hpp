#ifndef INPUT_IO_HPP
#define INPUT_IO_HPP

#include <iostream>
#include <vector>
#include <string>

namespace ivantsova {
  class IOGuard
  {
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

  struct DoubleSci
  {
    double value;
  };

  std::istream& operator>>(std::istream& is, DoubleSci& ds);
  std::ostream& operator<<(std::ostream& os, const DoubleSci& ds);
  bool operator<(const DoubleSci& lhs, const DoubleSci& rhs);
  bool operator==(const DoubleSci& lhs, const DoubleSci& rhs);

  struct UllBin
  {
    unsigned long long value;
  };

  std::istream& operator>>(std::istream& is, UllBin& ub);
  std::ostream& operator<<(std::ostream& os, const UllBin& ub);
  bool operator<(const UllBin& lhs, const UllBin& rhs);
  bool operator==(const UllBin& lhs, const UllBin& rhs);

  struct DelimeterIO
  {
    char expected;
    char& last;
  };

  std::istream& operator>>(std::istream& is, DelimeterIO del);

  struct KeyValueIO
  {
    std::string key;
    std::vector< bool >& is_been;
    struct DataStruct& ds;
  };

  std::istream& operator>>(std::istream& is, KeyValueIO inp);

  char check(std::istream& is, char expected);
}

#endif
