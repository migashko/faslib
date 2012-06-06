#ifndef FAS_SERIALIZATION_JSON_DESER_DESERIALIZE_ARRAY_HPP
#define FAS_SERIALIZATION_JSON_DESER_DESERIALIZE_ARRAY_HPP

#include <fas/serialization/json/deser/default_space_parser.hpp>
#include <fas/serialization/json/deser/deserialize_sequence.hpp>
namespace fas { namespace json{


template<typename AR, typename R, typename F>
inline R deserialize_array( AR ar, R r, F f)
{
  if (!r)
    throw unexpected_end_fragment();

  if (*(r++) != '[')
    throw expected_of("[", r.distance() - 1 );

  if (r && *r!=']') 
    r = deserialize_sequence(ar, r, f);

  if (!r) 
    throw unexpected_end_fragment();

  if (*(r++) != ']')
    throw expected_of("]", r.distance() - 1 );

  return r;
};



/*
template<typename AR, typename R, typename F>
inline R deserialize_array( AR ar, R r, F f)
{
  return deserialize_array(ar, r, f, deser::default_space_parser());
};
*/

}}

#endif

