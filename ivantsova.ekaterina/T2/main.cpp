#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <limits>
#include "data_struct.hpp"

int main() {
  using T = ivantsova::DataStruct;
  std::vector< T > data;

  using is_it = std::istream_iterator< T >;
  while (!std::cin.eof()) {
    std::copy(is_it{std::cin}, is_it{}, std::back_inserter(data));
    if (std::cin.fail() && !std::cin.eof()) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  std::sort(data.begin(), data.end());
  using os_it = std::ostream_iterator< T >;
  std::copy(data.begin(), data.end(), os_it{std::cout, "\n"});
  return 0;
}
