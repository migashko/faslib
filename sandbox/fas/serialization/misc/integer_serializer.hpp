#ifndef FAS_SERIALIZATION_MISC_INTEGER_SERIALIZER_HPP
#define FAS_SERIALIZATION_MISC_INTEGER_SERIALIZER_HPP

namespace fas { namespace misc{

template<typename T>
struct is_signed_integer
{
  enum { result = T(-1) < T(1) };

  static bool less_zero(T v)
  {
    return result && (v < 0);
  }
};

template<typename T>
struct integer_digits
{
  enum { result = sizeof(T)*2 + sizeof(T)/2 + sizeof(T)%2 + is_signed_integer<T>::result };
};

template<typename T, typename R>
inline R serialize_integer(T value, R r)
{
  typedef typename R::value_type value_type;

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

  for (beg = buffer; beg!=end; ++beg)
    *(r++)=*beg;

  return r;

}


/*
template<typename T, typename R>
class integer_serializer
{
  char _buf[integer_buffer_size<T>::result];

public:

  integer_serializer() {}

    template<typename P>
    P serialize(T v, P itr)
    {
      register char *beg = _buf;
      register char *end = _buf;
      if (v==0)
        *(end++) = '0';
      else
      {
        if ( is_signed_integer<T>::is_less_zero(v) ) 
        {
          *(end++)='-';
          ++beg;
          for( ; v!=0 ; ++end, v/=10) 
            *end = '0' - v%10;
        }
        else
          for( ; v!=0 ; ++end, v/=10) 
            *end = '0' + v%10;
      }
      for ( register char* cur = end ; cur-beg > 1;--cur, ++beg) 
      { *beg ^= *(cur-1); *(cur-1)^=*beg; *beg^=*(cur-1); }

      for (beg = _buf; beg!=end; ++beg)
        *(itr++)=*beg;

      return itr;
    }
};
*/

}}

#endif

