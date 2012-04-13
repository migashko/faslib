//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2012
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_RANGE_DETAIL_RANGE_HELPER_RANGE_HPP
#define FAS_RANGE_DETAIL_RANGE_HELPER_RANGE_HPP

#include <fas/range/typerange_flag.hpp>
#include <fas/range/range_category.hpp>
#include <fas/static_check/static_check.hpp>
#include <fas/typemanip/some_type.hpp>

namespace fas{

template< typename R>
struct range_helper<R, typerange_flag::range >
{
  enum { flag = typerange_flag::range };
  typedef R range;
  typedef typename range::difference_type   difference_type;
  typedef typename range::iterator   iterator;
  
  static inline range make_range(R r)
  {
    return r;
  }

  template<typename RR /*==R */>
  static inline
  typename RR::reverse_range
  make_rrange(RR r)
  {
    return r.reverse();
  }
  
  
  template<typename RR /*==R */>
  static inline forward_range< typename RR::iterator > make_orange(RR r, bool clear)
  {
    enum 
    {
      is_output_range = some_type< output_range_tag, typename RR::range_category_tag >::value,
      is_intput_range = some_type< input_range_tag, typename RR::range_category_tag >::value,
      not_input_or_output_range = static_check< !(is_output_range || is_intput_range ) >::value
    };
    
    typedef forward_range< typename RR::iterator > orange;
    
    if ( clear )
    {
      for ( orange i(r.begin(), r.end()); i ; ++i) 
        *i = typename RR::value_type();
    }
    
    return orange( r.begin(), r.end() );
  }

  static inline range make_erange(R r)
  {
    range rr = r;
    rr.advance( r.distance() );
    return rr;
  }

  static inline difference_type distance( R r )
  {
    return r.distance();
  }

  static inline difference_type distance( R& r, difference_type s)
  {
    r.advance(s);
  }

  static inline void decrease(R& r, difference_type cbeg, difference_type cend)
  {
    r.decrease(cbeg, cend);
  }

  
  static inline void increase(R& r, difference_type cbeg, difference_type cend)
  {
    r.increase(cbeg, cend);
  }
  
  static inline iterator begin(R r)
  {
    return r.begin();
  }

  static inline iterator end(R r)
  {
    return r.end();
  }

  template<typename Dist>
  static inline void advance( R r, Dist s)
  {
    r.advance(s);
  }

};


};

#endif
