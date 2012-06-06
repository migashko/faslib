#ifndef FAS_SERIALIZATION_JSON_SERIALIZE_ARRAY_HPP
#define FAS_SERIALIZATION_JSON_SERIALIZE_ARRAY_HPP

#include <fas/serialization/json/ser/serialize_sequence.hpp>
namespace fas { namespace json{


template<typename AR, typename R, typename F>
inline R serialize_array( AR ar, R r, F f)
{
  if ( r )
    *r++ = '[';
  r = serialize_sequence(ar, r, f);
  if ( r )
    *r++ = ']';
  return r;
};

}}

#endif


