//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2012
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_RANGE_DETAIL_RANGE_HELPER_OTHER_HPP
#define FAS_RANGE_DETAIL_RANGE_HELPER_OTHER_HPP

#include <fas/range/typerange_flag.hpp>
#include <fas/range/random_access_range.hpp>
#include <fas/range/forward_range.hpp>
#include <iterator>

namespace fas{

template< typename T>
struct range_helper<T, typerange_flag::other >
{
  enum { flag = typerange_flag::other };
  typedef random_access_range<T*> range;
  typedef std::reverse_iterator<T*> reverse_iterator;
  typedef random_access_range< std::reverse_iterator<T*> > reverse_range;
  typedef forward_range<T*> orange;
  
  typedef typename range::difference_type difference_type;
  
  template<typename TT>
  static inline reverse_range make_rrange(TT* v)
  {
    return reverse_range( reverse_iterator(&v), reverse_iterator(&v - 1) );
  }

  template<typename TT>
  static inline range make_range(TT& v)
  {
    return range(&v, &v + 1);
  }

  template<typename TT>
  static inline orange make_orange(TT& v, bool clear = false)
  {
    if ( clear )
      v = T();
    return orange(&v, &v + 1);
  }

  template<typename TT>
  static inline range make_erange(TT& v)
  {
    range r = make_range(v);
    ++r;
    return r;
  }

  template<typename TT>
  static inline difference_type distance( const TT& )
  {
    return 1;
  }
};

};

#endif
