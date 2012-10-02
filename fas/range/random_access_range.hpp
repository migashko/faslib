//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011, 2012
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_range_RANDOM_ACCESS_RANGE_HPP
#define FAS_range_RANDOM_ACCESS_RANGE_HPP

#include <fas/range/range_category.hpp>
#include <iterator>
#include <cassert>



namespace fas {


template<typename T>
class random_access_range
{
public:
  typedef random_access_range_tag range_category;

  typedef T iterator;
  typedef std::reverse_iterator<iterator> reverse_iterator;
  typedef random_access_range<reverse_iterator> reverse_range;
  typedef typename std::iterator_traits<T>::iterator_category iterator_category;
  typedef typename std::iterator_traits<T>::value_type        value_type;
  typedef typename std::iterator_traits<T>::difference_type   difference_type;
  typedef typename std::iterator_traits<T>::pointer           pointer;
  typedef typename std::iterator_traits<T>::reference         reference;

  random_access_range()
    : b(), e()
#ifndef NDEBUG
    , s(b)
#endif
  {};

  random_access_range(T b, T e)
    : b(b), e(e)
#ifndef NDEBUG
    , s(b)
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

  difference_type distance() const { return e-b; }

  void advance(difference_type c)
  {
    b+=c;
    assert( b <= e);
  }

#ifndef NDEBUG
  void increase(difference_type cbeg, difference_type cend)
  {
    s -= cbeg;
    assert( s <= b);
    e += cend;
    assert( e >= b);
  }
#else
  void increase(difference_type, difference_type cend)
  {
    e += cend;
    assert( e >= b);
  }
#endif


 #ifndef NDEBUG
  void decrease(difference_type cbeg, difference_type cend)
  {
    s += cbeg;
    assert( s <= b);
    e -= cend;
    assert( e >= b);
  }
#else
  void decrease(difference_type, difference_type cend)
  {
    e -= cend;
    assert( e >= b);
  }
#endif

  random_access_range<T>& operator++()
  {
    assert(b!=e);
    ++b;
    return *this;
  }

  random_access_range<T> operator++(int)
  {
    assert(b!=e);
    random_access_range<T> ans = *this;
    b++;
    return ans;
  }

  random_access_range<T>& operator--()
  {
#ifndef NDEBUG
    assert(b!=s);
#endif
    --b;
    return *this;
  }

  random_access_range<T> operator--(int)
  {
#ifndef NDEBUG
    assert(b!=s);
#endif
    random_access_range<T> ans = *this;
    b--;
    return ans;
  }

  bool operator == (const random_access_range<T>& r ) const
  {
    return b == r.b ;
  }

  bool operator != (const random_access_range<T>& r ) const
  {
    return !this->operator == (r);
  }

  bool operator < (const random_access_range<T>& r ) const
  {
    return b < r.b;
  }

  bool operator > (const random_access_range<T>& r ) const
  {
    return b > r.b;
  }

  bool operator <= (const random_access_range<T>& r ) const
  {
    return !this->operator >( r );
  }

  bool operator >= (const random_access_range<T>& r ) const
  {
    return !this->operator < ( r );
  }

  random_access_range<T>& operator += (difference_type n )
  {
    b += n;
    assert( e >= b);
    return *this;
  }

  random_access_range<T>& operator -= (difference_type n )
  {
    b -= n;
#ifndef NDEBUG
    assert( s <= b);
#endif
    return *this;
  }

  reference operator[] ( difference_type n ) const
  {
    //assert( e >= b + n);
    return b[n];
  }

protected:
  T b;
  T e;
#ifndef NDEBUG
  T s; // start
#endif
};


template<typename T, typename Dist>
inline random_access_range<T> operator +
  (
    random_access_range<T> r,
    Dist n
  )
{
  return r+=n;
}

template<typename T, typename Dist>
inline random_access_range<T> operator +
  (
    Dist n,
    random_access_range<T> r
  )
{
  return r+= n;
}

template<typename T, typename Dist>
inline random_access_range<T> operator -
  (
    random_access_range<T> r,
    Dist n
  )
{
  return r-= n;
}

template<typename T, typename Dist>
inline random_access_range<T> operator -
  (
    Dist n,
    random_access_range<T> r
  )
{
  return r -= n;
}

template<typename T>
inline typename random_access_range<T>::difference_type operator -
  (
    random_access_range<T> r1,
    random_access_range<T> r2
  )
{
  return r1.begin() - r2.begin();
}

}

#endif
