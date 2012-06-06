#ifndef FAS_SERIALIZATION_JSON_SERIALIZER_SERIALIZE_INTEGER_HPP
#define FAS_SERIALIZATION_JSON_SERIALIZER_SERIALIZE_INTEGER_HPP


namespace fas { namespace json{

template<typename T>
struct is_signed_integer
{
  enum { value = T(-1) < T(1) };

  static inline bool less_zero(T v)
  {
    return value && (v < 0);
  }
};

template<typename T>
struct integer_digits
{
  enum { result = sizeof(T)*2 + sizeof(T)/2 + sizeof(T)%2 + is_signed_integer<T>::value };
};

template<typename T, typename R>
inline R serialize_integer(T value, R r)
{
  typedef /*typename R::value_type*/char value_type;

  value_type buffer[integer_digits<T>::result];

  register value_type *beg = buffer;
  register value_type *end = buffer;

  if ( value == 0 )
  {
    *(end++) = '0';
  }
  else
  {
    if ( is_signed_integer<T>::less_zero(value) ) 
    {
      *(end++)='-';
      ++beg;
      for( ; value!=0 ; ++end, value/=10) 
        *end = '0' - value%10;
    }
    else
    {
      for( ; value!=0 ; ++end, value/=10) 
        *end = '0' + value%10;
    }
  }

  for ( register value_type* cur = end ; cur-beg > 1;--cur, ++beg) 
  {
    *beg ^= *(cur-1);
    *(cur-1)^=*beg;
    *beg^=*(cur-1); 
  }

  for (beg = buffer; r && beg!=end; ++beg)
    *(r++)=*beg;

  return r;
}

}}

#endif
