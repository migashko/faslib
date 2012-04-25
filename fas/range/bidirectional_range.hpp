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
    : b(), e(), s(b)
  {};

  explicit bidirectional_range(T b, T e)
    : b(b), e(e), s(b)
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
  
  void increase(difference_type cbeg, difference_type cend)
  {
    std::advance( s, 0 - cbeg );
    std::advance( e, cend );
    
    assert( s <= b);
    assert( e >= b);
  }

  void decrease(difference_type cbeg, difference_type cend)
  {
    std::advance( s, cbeg );
    std::advance( e, 0 - cend );

    assert( s <= b);
    assert( e >= b);
  }


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
    assert(b!=s);
    --b; 
    return *this; 
  }

  bidirectional_range<T> operator--(int) 
  {
    assert(b!=s);
    bidirectional_range<T> ans = *this;   
    b--; 
    return ans; 
  }

  bool operator == (const bidirectional_range<T>& r ) const { return b == r.b && e==r.e;  }

  bool operator != (const bidirectional_range<T>& r ) const { return !(*this == r); }

protected:
  T b;
  T e;
  T s; // start
};

}

#endif
