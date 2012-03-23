#ifndef FAS_range_STRING_RANGE_HPP
#define FAS_range_STRING_RANGE_HPP

#include <fas/range/range_category.hpp>

#include <iterator>
#include <cassert>
#include <cstring>

namespace fas{

// TODO: сдеать как адаптер к range
template<typename T>
class string_range
{
public:
  typedef random_access_range_tag range_category;
  
  typedef T iterator;
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

  /*const*/ reference operator*() const { return *b; }

  //reference operator*() { return *b; }

  // pointer operator ->() { return &(*b);}

  /*const*/ pointer operator ->() const  { return &(*b);}

  /*const T*/ iterator begin() const { return b; }
  
  /*const T*/ iterator end() const { return _end(); }

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

// TODO: random access range operation
protected:

  T _end() const
  {
    if ( !e)
    {
      e = b;
      // std::advance( e, std::strlen(e) );
      for ( ;*e!='\0';++e);
      
    }
    return e; 
  }

  T b;
  mutable T e;
  T s; // start
};

}

#endif
