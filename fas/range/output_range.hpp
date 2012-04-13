//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011, 2012
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_range_OUTPUT_RANGE_HPP
#define FAS_range_OUTPUT_RANGE_HPP

#include <fas/range/range_category.hpp>
#include <iterator>

namespace fas{

template<typename T, typename ValueType>
class output_range
{
public:
  typedef output_range_tag range_category;
  
  typedef T iterator;

  typedef ValueType        value_type;
  typedef typename std::iterator_traits<T>::iterator_category iterator_category;
  typedef typename std::iterator_traits<T>::difference_type   difference_type;
  typedef typename std::iterator_traits<T>::pointer           pointer;
  typedef typename std::iterator_traits<T>::reference         reference;
  
  output_range()
    : b()
  {}

  explicit output_range(T b)
    : b(b)
  {}

  operator bool () const { return true; }

  iterator& operator*() { return b; }

  template<typename V>
  output_range<T, ValueType>& operator=(const V& value)
  {
    *b = value;
    return *this;
  }

  output_range<T, ValueType>& operator++() 
  {
    return *this; 
  }

  output_range<T, ValueType>& operator++(int) 
  {
    return *this; 
  }

protected:
  T b;
};

}

#endif

