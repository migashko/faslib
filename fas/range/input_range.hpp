//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011, 2012
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_RANGE_INPUT_RANGE_HPP
#define FAS_RANGE_INPUT_RANGE_HPP

#include <fas/range/range_category.hpp>
#include <iterator>
#include <cassert>

namespace fas {

template<typename T, typename ValueType>
class input_range
{
public:
  typedef input_range_tag range_category;

  typedef T iterator;

  typedef ValueType value_type;
  typedef typename std::iterator_traits<T>::iterator_category iterator_category;
  typedef typename std::iterator_traits<T>::difference_type   difference_type;
  typedef typename std::iterator_traits<T>::pointer           pointer;
  typedef typename std::iterator_traits<T>::reference         reference;

  class proxy {
    ValueType keep_;
  public:
    explicit proxy (ValueType c) : keep_(c){ }
    ValueType operator*() const { return keep_; }
  };

  input_range()
    : b(), e()
  {}

  explicit input_range(T b1, T e1)
    : b(b1), e(e1)
  {}

  operator bool () const { return b!=e; }

  value_type operator*() const { return *b; }

  pointer operator ->() const  { return &(*b);}

  iterator begin() const { return b; }

  iterator end() const { return e; }

  input_range<T, ValueType>& operator++()
  {
    assert(b!=e);
    ++b;
    return *this;
  }

  proxy operator++(int)
  {
    assert(b!=e);
    proxy p( *b );
    b++;
    return p;
  }

  difference_type distance() const { return std::distance(b, e); }

  void advance(difference_type s)
  {
    std::advance(b, s);
  }

  bool operator == (const input_range<T, ValueType>& r ) const
  {
    return b == r.b && e==r.e;
  }

  bool operator != (const input_range<T, ValueType>& r ) const
  {
    return !(*this == r);
  }

protected:
  T b;
  T e;
};

}

#endif
