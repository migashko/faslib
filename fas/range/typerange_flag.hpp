#ifndef FAS_RANGE_TYPERANGE_FLAG_HPP
#define FAS_RANGE_TYPERANGE_FLAG_HPP

#include <fas/typemanip/has_typename.hpp>
#include <fas/typemanip/is_array.hpp>
#include <fas/typemanip/is_pointer.hpp>
#include <fas/range/is_stream.hpp>

namespace fas{

FAS_HAS_TYPENAME(has_iterator_category, iterator_category);
FAS_HAS_TYPENAME(has_range_category, range_category);
FAS_HAS_TYPENAME(has_iterator, iterator);

struct typerange_flag
{
  struct shift
  {
    enum
    {
      other     = 0,
      pointer   = 1,
      array     = 2,
      range     = 3,
      iterator  = 4,
      container = 5,
      stream    = 6
    };
  };
  
  enum
  {
    other     = 0,                      // 0
    pointer   = 1 << shift::pointer,    // 2
    array     = 1 << shift::array,      // 4
    range     = 1 << shift::range,      // 8
    iterator  = 1 << shift::iterator,   // 16
    container = 1 << shift::container,  // 32
    stream    = 1 << shift::stream      // 64
  };

  template<typename T>
  struct make
  {
    enum
    {
      array_flag = is_array<T>::value, 
      pointer_flag = !array_flag && is_pointer<T>::value, 
      iterator_flag = !pointer_flag && has_iterator_category<T>::value,
      container_flag = !iterator_flag && has_iterator<T>::value,
      range_flag = !iterator_flag && has_range_category<T>::value,
      stream_flag = !range_flag && is_stream<T>::value
    };

    enum
    {
      value =
          ( array_flag     << shift::array )
        | ( pointer_flag   << shift::pointer )
        | ( iterator_flag  << shift::iterator )
        | ( container_flag << shift::container )
        | ( range_flag     << shift::range )
        | ( stream_flag    << shift::stream )
    };
  };
};


};

#endif

