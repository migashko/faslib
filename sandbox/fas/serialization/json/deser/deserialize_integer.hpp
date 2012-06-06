#ifndef FAS_SERIALIZATION_JSON_DESER_DESERIALIZE_INTEGER_HPP
#define FAS_SERIALIZATION_JSON_DESER_DESERIALIZE_INTEGER_HPP


namespace fas { namespace json{

template<typename V, typename R >
inline R deserialize_integer(  V& v, R r )
{
  if( !r )
    return r;

  v = 0;

  register bool neg = *r=='-';
   
  if ( neg ) ++r;
   
  if ( !r || *r < '0' || *r > '9')
    return r;

  // цифры с первым нулем запрещены (напр 001), только 0
  // while пропустить 000 ? 
  if (*r=='0')
    return ++r;

  for ( ;r; ++r )
  {
    if (*r < '0' || *r > '9') 
      break;
    v = v*10 + (*r- '0');
  }
  if (neg) v*=-1;
  return r;
};

}}

#endif
