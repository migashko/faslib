#ifndef FAS_SERIALIZATION_JSON_SERIALIZER_SERIALIZE_REAL_HPP
#define FAS_SERIALIZATION_JSON_SERIALIZER_SERIALIZE_REAL_HPP

#include <sstream>

namespace fas { namespace json{


template<typename T, typename R>
inline R serialize_real(T value, R r)
{
  std::stringstream ss;
  ss << value;
  register typename R::value_type chr;
  while ( r )
  {
    ss >> chr;
    if (!ss) break;
    *(r++) = chr;
  }
  return r;
}

}}

#endif
