//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011, 2012
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_RANGE_BIDIRECTIONAL_RANGE_HPP
#define FAS_RANGE_BIDIRECTIONAL_RANGE_HPP

#include <fas/range/range_category.hpp>
#include <iterator>
#include <cassert>

namespace fas{

template<typename T>
class bidirectional_range
{
public:
  typedef bidirectional_range_tag range_category;
  typedef T iterator;
  typedef std::reverse_iterator<T> reverse_iterator;
  typedef bidirectional_range<reverse_iterator> reverse_range;
  typedef typename std::iterator_traits<T>::iterator_category iterator_category;
  typedef typename std::iterator_traits<T>::value_type        value_type;
  typedef typename std::iterator_traits<T>::difference_type   difference_type;
  typedef typename std::iterator_traits<T>::pointer           pointer;
  typedef typename std::iterator_traits<T>::reference         reference;

  bidirectional_range()
    : b(), e()
#ifndef NDEBUG
    , s(b)
#endif
  {};

  explicit bidirectional_range(T b1, T e1)
    : b(b1), e(e1)
#ifndef NDEBUG
    , s(b1)
#endif
  {};

  operator bool () const { return b!=e; }

  reference operator*() const { return *b; }

  pointer operator ->() const  { return &(*b);}

  iterator begin() const { return b; }

  iterator end() const { return e; }

  reverse_iterator rbegin() const { return reverse_iterator(e); }

  reverse_iterator rend() const { return reverse_iterator(b); }
  
  reverse_range reverse() const { return reverse_range( rbegin(), rend() ); }

  difference_type distance() const { return std::distance(b, e); }

  void advance(difference_type c)  { std::advance(b, c); }

#ifndef NDEBUG
  void increase(difference_type cbeg, difference_type cend)
  {
    std::advance( s, 0 - cbeg );
    assert( s <= b);
    std::advance( e, cend );
    assert( e >= b);
  }

  void decrease(difference_type cbeg, difference_type cend)
  {
    std::advance( s, cbeg );
    assert( s <= b);
    std::advance( e, 0 - cend );
    assert( e >= b);
  }

# else
  void increase(difference_type , difference_type cend)
  {
    std::advance( e, cend );
    assert( e >= b);
  }

  void decrease(difference_type , difference_type cend)
  {
    std::advance( e, 0 - cend );
    assert( e >= b);
  }
# endif

  bidirectional_range<T>& operator++() 
  {
    assert(b!=e);
    ++b;
    return *this; 
  }

  bidirectional_range<T> operator++(int) 
  {
    assert(b!=e);
    bidirectional_range<T> ans = *this;   
    b++; 
    return ans; 
  }

  bidirectional_range<T>& operator--() 
  {
#ifndef NDEBUG
    assert(b!=s);
#endif
    --b; 
    return *this; 
  }

  bidirectional_range<T> operator--(int) 
  {
#ifndef NDEBUG
    assert(b!=s);
#endif
    bidirectional_range<T> ans = *this;   
    b--; 
    return ans; 
  }

  bool operator == (const bidirectional_range<T>& r ) const { return b == r.b && e==r.e;  }

  bool operator != (const bidirectional_range<T>& r ) const { return !(*this == r); }

protected:
  T b;
  T e;
#ifndef NDEBUG
  T s; // start
#endif
};

}

#endif
