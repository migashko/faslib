#ifndef FAS_range_RANDOM_ACCESS_RANGE_HPP
#define FAS_range_RANDOM_ACCESS_RANGE_HPP

#include <fas/range/range_category.hpp>

#include <iterator>
#include <cassert>
#include <stdexcept>


namespace fas {

template<typename T>
class random_access_range;



template<typename T>
class random_access_range
{
public:
  typedef random_access_range_tag range_category;
  
  typedef T iterator;
  /* typedef const T const_iterator; */ 
  typedef typename std::iterator_traits<T>::iterator_category iterator_category;
  typedef typename std::iterator_traits<T>::value_type        value_type;
  typedef typename std::iterator_traits<T>::difference_type   difference_type;
  typedef typename std::iterator_traits<T>::pointer           pointer;
  typedef typename std::iterator_traits<T>::reference         reference;
  
 
  explicit random_access_range()
    : b(), e(), s(b)
  {};
  
  /*explicit */random_access_range(T b, T e)
    : b(b), e(e), s(b)
  {};

  operator bool () const { return b!=e; }

  /*! const reference operator*() const { return *b; } */

  reference operator*() const { return *b; }

  /* pointer operator ->() { return &(*b);} */

  /*const */ pointer operator ->() const  { return &(*b);}

  /*const T*/ iterator begin() const { return b; }

  /*const T*/ iterator end() const { return e; }

  difference_type distance() const { return std::distance(b, e); }

  random_access_range<T>& advance(difference_type c)
  {
    std::advance(b, c);
    return *this;
  }

  random_access_range<T>& narrow(difference_type c)
  {
    e -= c;
    return *this;
  }

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
    assert(b!=s);
    --b;
    return *this;
  }

  random_access_range<T> operator--(int)
  {
    assert(b!=s);
    random_access_range<T> ans = *this;
    b--;
    return ans;
  }

  bool operator == (const random_access_range<T>& r ) const { return b == r.b /*&& e==r.e*/;  }

  bool operator != (const random_access_range<T>& r ) const { return /*!(*this == r)*/ !this->operator == (r); }

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

  random_access_range<T>& operator += (std::ptrdiff_t n )
  {
    b += n;
    return *this;
  }

  random_access_range<T>& operator -= (std::ptrdiff_t n )
  {
    b -= n;
    return *this;
  }

  /*const value_type&*/reference operator[] ( std::ptrdiff_t n ) const
  {
    return b[n];
  }

  /*value_type& operator[] ( std::ptrdiff_t n )
  {
    return *(b+n);
  }*/


  
  template<typename TT, typename PP>
  friend inline random_access_range<TT> operator + ( random_access_range<TT> r, PP n );

  template<typename TT, typename PP>
  friend inline random_access_range<TT> operator + ( PP n, random_access_range<TT> r);

  template<typename TT, typename PP>
  friend inline random_access_range<TT> operator - ( random_access_range<TT> r, PP n );

  template<typename TT, typename PP>
  friend inline random_access_range<TT> operator - ( PP n, random_access_range<TT> r);

  template<typename TT>
  friend inline std::ptrdiff_t operator - ( random_access_range<TT> r1, random_access_range<TT> r2);
  

protected:
  T b;
  T e;
  T s; // start
};


template<typename T, typename P>
inline random_access_range<T> operator + ( random_access_range<T> r, P n )
{
  return random_access_range<T>( r.b + n, r.e );
}

template<typename T, typename P>
inline random_access_range<T> operator + ( P n, random_access_range<T> r )
{
  return random_access_range<T>( r.b + n, r.e );
}

template<typename T, typename P>
inline random_access_range<T> operator - ( random_access_range<T> r, P n )
{
  return random_access_range<T>( r.b - n, r.e );
}

template<typename T, typename P>
inline random_access_range<T> operator - ( P n, random_access_range<T> r )
{
  return random_access_range<T>( r.b - n, r.e );
}

template<typename T>
inline std::ptrdiff_t operator - ( random_access_range<T> r1, random_access_range<T> r2 )
{
  return r1.b - r2.b;
  /*return std::distance( r2.begin(), r1.begin() );*/
}



#define FAS_OP(C, OP)\
template<typename T, typename P>  inline C<T> operator OP (C<T> p1, P p2) { /*static_check<false> operation_is_not_allowed;*/ return p1.b OP p2; };\
template<typename T, typename P>  inline C<T> operator OP (P p1, C<T> p2) { /*static_check<false> operation_is_not_allowed;*/ return p2.b OP p1; };\
template<typename T>\
inline std::ptrdiff_t operator OP (C<T> p1, C<T> p2) \
{ /*static_check<false> operation_is_not_allowed;*/ return std::distance( p2.begin(), p1.begin() ) ; }

#define FAS_ALL_OP(C) FAS_OP(C, -) FAS_OP(C, +) FAS_OP(C, /)


}

#endif
