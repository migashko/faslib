#ifndef FAS_SERIALIZATION_JSON_DESER_DESERIALIZE_BOOLEAN_HPP
#define FAS_SERIALIZATION_JSON_DESER_DESERIALIZE_BOOLEAN_HPP


namespace fas { namespace json{

template<typename R, typename V>
inline R deserialize_boolean( R r, V& v )
{
  R income = r;
  if ( *r == 't' )
  {
    if ( *(++r) != 'r' ) return income;
    if ( *(++r) != 'u' ) return income;
    if ( *(++r) != 'e' ) return income;
    v = true;
    return r;
  }
  else if (*r == 'f')
  {
    if ( *(++r) != 'a' ) return income;
    if ( *(++r) != 'l' ) return income;
    if ( *(++r) != 's' ) return income;
    if ( *(++r) != 'e' ) return income;
    v = false;
    return r;
  }
  return income;
}

}}

#endif
