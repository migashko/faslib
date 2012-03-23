#ifndef FAS_range_TRIVIAL_RANGE_HPP
#define FAS_range_TRIVIAL_RANGE_HPP

#include <fas/range/range_category.hpp>

#include <iterator>

namespace fas{

template<typename T>
class trivial_range
{
public:
  typedef trivial_range_tag range_category;
  
  typedef T iterator;
  typedef typename std::iterator_traits<T>::iterator_category iterator_category;
  typedef typename std::iterator_traits<T>::value_type        value_type;
  typedef typename std::iterator_traits<T>::difference_type   difference_type;
  typedef typename std::iterator_traits<T>::pointer           pointer;
  typedef typename std::iterator_traits<T>::reference         reference;

  
  trivial_range()
    : b() 
  {}
  
  
  explicit trivial_range(T b)
    : b(b)
  {}

  const iterator begin() const { return b; }

  operator bool () const { return true; }

  bool operator == (const trivial_range<T>& r ) const { return b == r.b;  }

  bool operator != (const trivial_range<T>& r ) const { return !(*this == r); }

  /*const*/ reference operator*() const { return *b; }

  //reference operator*() { return *b; }

  // pointer operator ->() { return &(*b);}

  /*const */pointer operator ->() const  { return &(*b);}

protected:
  T b;
};

}

#endif
