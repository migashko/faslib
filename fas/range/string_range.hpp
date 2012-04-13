//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_RANGE_STRING_RANGE_HPP
#define FAS_RANGE_STRING_RANGE_HPP

#include <fas/range/range_category.hpp>

#include <iterator>
#include <cassert>
#include <cstring>

namespace fas{

template<typename T>
class string_range
{
public:
  typedef random_access_range_tag range_category;
  
  typedef T iterator;
  typedef std::reverse_iterator<iterator> reverse_iterator;
  typedef string_range<reverse_iterator> reverse_range;
  typedef typename std::iterator_traits<T>::iterator_category iterator_category;
  typedef typename std::iterator_traits<T>::value_type        value_type;
  typedef typename std::iterator_traits<T>::difference_type   difference_type;
  typedef typename std::iterator_traits<T>::pointer           pointer;
  typedef typename std::iterator_traits<T>::reference         reference;

  string_range()
    : b(), e(0), s(b)
  {};

  explicit string_range(T b)
    : b(b), e(0), s(b)
  {};

  operator bool () const { return *b!='\0'; }

  reference operator*() const { return *b; }

  pointer operator ->() const  { return &(*b);}

  iterator begin() const { return b; }
  
  iterator end() const { return _end(); }
  
  reverse_iterator rbegin() const { return reverse_iterator( this->end() ); }

  reverse_iterator rend() const { return reverse_iterator( this->begin() ); }

  difference_type distance() const { return std::distance(b, _end() ); }
  
  string_range<T>& advance(difference_type c)  { std::advance(b, c); return *this; }

  string_range<T>& operator++() 
  {
    assert(*b!='\0');
    ++b; 
    return *this; 
  }

  string_range<T> operator++(int) 
  {
    assert(*b!='\0');
    string_range<T> ans = *this;
    b++;
    return ans; 
  }

  string_range<T>& operator--()
  {
    assert(b!=s);
    --b;
    return *this; 
  }

  string_range<T> operator--(int) 
  {
    assert(b!=s);
    string_range<T> ans = *this;
    b--;
    return ans;
  }

  bool operator == (const string_range<T>& r ) const { return b == r.b;  }

  bool operator != (const string_range<T>& r ) const { return !(*this == r); }

  bool operator < (const string_range<T>& r ) const 
  {
    return b < r.b;
  }

  bool operator > (const string_range<T>& r ) const 
  {
    return b > r.b;
  }

  bool operator <= (const string_range<T>& r ) const
  {
    return !this->operator >( r );
  }

  bool operator >= (const string_range<T>& r ) const
  {
    return !this->operator < ( r );
  }

  string_range<T>& operator += (difference_type n )
  {
    b += n;
    assert( _end() >= b);
    return *this;
  }

  string_range<T>& operator -= (difference_type n )
  {
    b -= n;
    assert( s <= b);
    return *this;
  }

  reference operator[] ( difference_type n ) const
  {
    assert( _end() >= b + n);
    return b[n];
  }

protected:

  T _end() const
  {
    if ( !e)
    {
      e = b;
      e += std::strlen(e);
    }
    return e; 
  }

  T b;
  mutable T e;
  T s; // start
};

template<typename T, typename Dist>
inline string_range<T> operator + 
  ( 
    string_range<T> r, 
    Dist n 
  )
{
  return r+=n;
}

template<typename T, typename Dist>
inline string_range<T> operator + 
  ( 
    Dist n, 
    string_range<T> r 
  )
{
  return r+= n;
}

template<typename T, typename Dist>
inline string_range<T> operator - 
  ( 
    string_range<T> r, 
    Dist n 
  )
{
  return r-= n;
}

template<typename T, typename Dist>
inline string_range<T> operator - 
  ( 
    Dist n, 
    string_range<T> r 
  )
{
  return r -= n;
}

template<typename T>
inline typename string_range<T>::difference_type operator - 
  ( 
    string_range<T> r1, 
    string_range<T> r2 
  )
{
  return r1.begin() - r2.begin();
}

}

#endif
