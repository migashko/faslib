#ifndef FAS_SERIALIZATION_JSON_SER_SERIALIZE_BOOLEAN_HPP
#define FAS_SERIALIZATION_JSON_SER_SERIALIZE_BOOLEAN_HPP


namespace fas { namespace json{


template<typename T, typename R>
inline R serialize_boolean(T value, R r)
{
  if (!r) return r;
  if ( value )
  {
    *r = 't'; ++r; if (!r) return r;
    *r = 'r'; ++r; if (!r) return r;
    *r = 'u'; ++r; if (!r) return r;
    *r = 'e'; ++r;
  }
  else
  {
    *r = 'f'; ++r; if (!r) return r;
    *r = 'a'; ++r; if (!r) return r;
    *r = 'l'; ++r; if (!r) return r;
    *r = 's'; ++r; if (!r) return r;
    *r = 'e'; ++r;
  }
  return r;
}

}}

#endif
