#ifndef FAS_range_FORWARD_RANGE_HPP
#define FAS_range_FORWARD_RANGE_HPP

#include <fas/range/range_category.hpp>

#include <iterator>
#include <cassert>

namespace fas{

template<typename T>
class forward_range
{
public:
  typedef forward_range_tag range_category;
  
  typedef T iterator;
  
  typedef typename std::iterator_traits<T>::iterator_category iterator_category;
  typedef typename std::iterator_traits<T>::value_type        value_type;
  typedef typename std::iterator_traits<T>::difference_type   difference_type;
  typedef typename std::iterator_traits<T>::pointer           pointer;
  typedef typename std::iterator_traits<T>::reference         reference;

  forward_range()
    : b(), e()
  {};

  explicit forward_range(T b, T e)
    : b(b), e(e)
  {};

  operator bool () const { return b!=e; }

  reference operator*() const { return *b; }

  pointer operator ->() const  { return &(*b);}

  iterator begin() const { return b; }

  iterator end() const { return e; }

  difference_type distance() const { return std::distance(b, e); }

  /*forward_range<T>&*/
  void advance(difference_type s)  
  {
    std::advance(b, s); 
    //return *this;
  }

  forward_range<T>& operator++() 
  {
    assert(b!=e);
    ++b;
    return *this; 
  }

  forward_range<T> operator++(int)
  {
    assert(b!=e);
    forward_range<T> ans = *this;
    b++;
    return ans;
  }

  bool operator == (const forward_range<T>& r ) const { return b == r.b && e==r.e;  }

  bool operator != (const forward_range<T>& r ) const { return !(*this == r); }

protected:
  T b;
  T e;
};

}

#endif
