//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2012
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_RANGE_INPUT_STREAM_RANGE_HPP
#define FAS_RANGE_INPUT_STREAM_RANGE_HPP

#include <fas/range/input_stream_range.hpp>

namespace fas {

template<typename T, typename ValueType>
class input_stream_range
  : public input_range<T, ValueType>
{
  typedef input_range<T, ValueType> super;
public:
  
  typedef typename super::range_category    range_category;
  typedef typename super::iterator          iterator;
  typedef typename super::value_type        value_type;
  typedef typename super::iterator_category iterator_category;
  typedef typename super::difference_type   difference_type;
  typedef typename super::pointer           pointer;
  typedef typename super::reference         reference;
  typedef typename super::proxy             proxy;
  
  input_stream_range()
    : super(), _pos()
  {};

  explicit input_stream_range(T b1, T e1)
    : super(b1, e1), _pos()
  {};

  input_stream_range<T, ValueType>& operator++() 
  {
    ++_pos;
    super::operator++();
    return *this; 
  }

  proxy operator++(int) 
  {
    ++_pos;
    return super::operator++(0); 
  }

  difference_type distance() const { return _pos; }
  
  void advance(difference_type s)  
  { 
    _pos += s;
    super::advance(s);
  }
  
  bool operator == (const input_stream_range<T, ValueType>& r ) const 
  {
    return super::operator==(r) && _pos == r._pos;  
  }

  bool operator != (const input_stream_range<T, ValueType>& r ) const 
  {
    return !(*this == r); 
  }

private:
  difference_type _pos;
};

}

#endif
