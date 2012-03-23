#ifndef FAS_SERIALIZATION_INTEGER2STRING_HPP
#define FAS_SERIALIZATION_INTEGER2STRING_HPP

#include <fas/range/string_range.hpp>
namespace fas {

template<typename T>
class integer2string
{
public:
  typedef string_range<const char*> range_type;
  enum { is_signed = T(-1) < T(1) };
  enum { max_digits = sizeof(T)*2 + sizeof(T)/2 + sizeof(T)%2 + is_signed };

  integer2string()
  {
    _buff[0]='0';
    _buff[1]='\0';
  }

  integer2string(T value)
  {
    this->operator = (value);
  }

  static bool less_zero(T v)
  {
    return is_signed && (v < 0);
  }
  
  void operator = (T value)
  {
    register char *beg = _buff;
    register char *end = _buff;

    if ( value == 0 )
    {
      *(end++) = '0';
    }
    else
    {
      if ( less_zero(value) ) 
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

    for ( register char* cur = end ; cur-beg > 1; --cur, ++beg) 
    {
      *beg ^= *(cur-1);
      *(cur-1)^=*beg;
      *beg^=*(cur-1); 
    }

    *(end++) = '\0';
  }

  operator const char* () const
  {
    return _buff;
  }

  const char* c_str() const
  {
    return _buff;
  }

  operator range_type () const
  {
    return range_type(_buff);
  }

  range_type get_range() const
  {
    return range_type(_buff);
  }

private:

  char _buff[max_digits];
  
};

}

#endif
