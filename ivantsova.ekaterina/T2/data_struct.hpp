#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP

#include <iostream>
#include <string>
#include "input_io.hpp"

namespace ivantsova {
  struct DataStruct {
    DoubleSci key1;
    UllBin key2;
    std::string key3;
  };

  std::istream& operator>>(std::istream& is, DataStruct& ds);
  std::ostream& operator<<(std::ostream& os, const DataStruct& ds);
  bool operator<(const DataStruct& lhs, const DataStruct& rhs);
}

#endif
