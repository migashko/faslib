//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011, 2012
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_range_INPUT_RANGE_HPP
#define FAS_range_INPUT_RANGE_HPP

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
    proxy (ValueType c) : keep_(c){ }
    ValueType operator*() {return keep_;}
  };
  
  input_range()
    : b(), e()
  {};

  explicit input_range(T b, T e)
    : b(b), e(e)
  {};

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

/*#include <fas/range/advance.hpp>
#include <fas/range/distance.hpp>
*/

namespace fas {

template<typename T, typename WR>
class input_range_wrapper
{
public:
  typedef input_range_tag range_category;

  typedef T input_range;
  typedef WR wrapper_range;

  typedef typename wrapper_range::value_type value_type;
  typedef typename wrapper_range::iterator iterator;
  typedef typename input_range::iterator input_iterator;
  typedef typename std::iterator_traits<input_iterator>::iterator_category iterator_category;
  typedef typename std::iterator_traits<input_iterator>::difference_type   difference_type;
  typedef typename std::iterator_traits<input_iterator>::pointer           pointer;
  typedef typename std::iterator_traits<input_iterator>::reference         reference;

  class proxy {
    value_type keep_;
  public:
    proxy (value_type c) : keep_(c){ }
    value_type operator*() {return keep_;}
  };

  /*
  input_range_wrapper()
    : ir(), wr()
  {};
  */

  explicit input_range_wrapper(input_range ir, wrapper_range wr)
    : ir(ir), wr(wr)
  {
    *wr = *ir;
  };

  operator bool () const { return ir; }

  value_type operator*() const
  {
    *wr = static_cast<value_type>(*ir);
    return *wr;
  }

  pointer operator ->() const  { return &(*wr);}

  iterator begin() const { return wr.begin(); }

  iterator end() const { return wr.end(); }

  input_range_wrapper<T, WR>& operator++()
  {
    *(wr++) = *(ir++);
    return *this;
  }

  proxy operator++(int)
  {
    proxy p( *wr );
    *(wr++) = *(ir++);
    return p;
  }

  difference_type distance() const { /*return distance(ir);*/ return 0; }

  void advance(difference_type s)
  {
    //advance(ir, s);
  }

  bool operator == (const input_range_wrapper<T, WR>& r ) const
  {
    return wr == r.wr;
  }

  bool operator != (const input_range_wrapper<T, WR>& r ) const
  {
    return !(*this == r);
  }

protected:
  T  ir;
  mutable WR wr;
};


}

#endif
