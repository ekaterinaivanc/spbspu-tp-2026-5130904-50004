#include <vector>
#include "data_struct.hpp"
#include "input_io.hpp"

std::istream& ivantsova::operator>>(std::istream& is, ivantsova::DataStruct& ds)
{
  std::istream::sentry s(is);
  if (!s) {
    return is;
  }
  ivantsova::IOGuard guard(is);
  ivantsova::DataStruct inp;
  char last = 0;
  std::vector< bool > is_been(3, false);
  std::string k1, k2, k3;

  is >> ivantsova::DelimeterIO{'(', last} >> ivantsova::DelimeterIO{':', last} >> k1 >> ivantsova::KeyValueIO{k1, is_been, inp}
    >> ivantsova::DelimeterIO{':', last} >> k2 >> ivantsova::KeyValueIO{k2, is_been, inp} >> ivantsova::DelimeterIO{':', last}
      >> k3 >> ivantsova::KeyValueIO{k3, is_been, inp} >> ivantsova::DelimeterIO{':', last} >> ivantsova::DelimeterIO{')', last};

  if (is && is_been[0] && is_been[1] && is_been[2]) {
    ds = inp;
  }
  return is;
}

std::ostream& ivantsova::operator<<(std::ostream& os, const ivantsova::DataStruct& ds)
{
  ivantsova::IOGuard g(os);
  os << "(:key1 " << ds.key1 << ":key2 " << ds.key2 << ":key3 \"" << ds.key3 << "\":)";
  return os;
}

bool ivantsova::operator<(const ivantsova::DataStruct& lhs, const ivantsova::DataStruct& rhs)
{
  if (!(lhs.key1 == rhs.key1)) {
    return lhs.key1 < rhs.key1;
  }
  if (!(lhs.key2 == rhs.key2)) {
    return lhs.key2 < rhs.key2;
  }
  return lhs.key3 < rhs.key3;
}
