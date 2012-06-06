#ifndef FAS_SERIALIZATION_JSON_SERIALIZER_AD_INTEGER_HPP
#define FAS_SERIALIZATION_JSON_SERIALIZER_AD_INTEGER_HPP

#include <fas/range/typerange.hpp>
#include <fas/range/range_traits.hpp>
#include <fas/serialization/json/except/try_throw.hpp>
#include <fas/serialization/json/except/out_of_range.hpp>


namespace fas{ namespace json{ namespace ser{

struct ad_integer
{
  template<typename T, typename M, typename V>
  bool check(T&, M, V )
  {
    return true;
  };

  template<typename T, typename M, typename V, typename R>
  R operator()(T& t, M, V v, R r)
  {
    return this->serialize_integer( t, v, r );
  }

protected:
  
  template<typename T, int C>
  struct less_zero_helper
  {
    static inline bool less_zero(T v)
    {
      return (v < 0);
    }
  };

  template<typename T>
  struct less_zero_helper<T, false>
  {
    static inline bool less_zero(T v) 
    {
      return false; 
    };
  };
  

  template<typename T>
  struct is_signed_integer
  {
    enum { value = T(-1) < T(1) };

    static inline bool less_zero(T v)
    {
      return less_zero_helper<T, value>::less_zero(v);
      //return value && (v < 0);
    }
  };

  template<typename T>
  struct integer_digits
  {
    enum { result = sizeof(T)*2 + sizeof(T)/2 + sizeof(T)%2 + is_signed_integer<T>::value };
  };

  template<typename T, typename V, typename R>
  inline R serialize_integer(T& t, V value, R r)
  {
    typedef typename range_traits<R>::value_type value_type;

    value_type buffer[integer_digits<V>::result];

    register value_type *beg = buffer;
    register value_type *end = buffer;

    if ( value == 0 )
    {
      *(end++) = '0';
    }
    else
    {
      if ( is_signed_integer<V>::less_zero(value) )
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
    {
      if ( !r )
        return throw_(t, out_of_range(), r);
      *(r++)=*beg;
    }

    return r;
}

};

}}}


#endif
