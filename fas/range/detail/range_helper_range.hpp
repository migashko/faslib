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

  
  
  static inline range make_range(R r)
  {
    return r;
  }

  template<typename RR /*==R */>
  static inline
  typename range_helper< typename RR::reverse_iterator, typerange_flag::range >::range
  make_rrange(RR r)
  {
    typename range_helper< 
      typename RR::reverse_iterator, 
      typerange_flag::range 
    >::range( r.rbegin(), r.rend() );
  }
  
  
  template<typename RR /*==R */>
  static inline range make_orange(RR r, bool clear)
  {
    enum 
    {
      is_output_range = some_type< output_range_tag, typename RR::range_category_tag >::value,
      is_intput_range = some_type< input_range_tag, typename RR::range_category_tag >::value,
      not_input_or_output_range = static_check< !(is_output_range || is_intput_range ) >::value
    };
    if ( clear )
      for ( R i = r; i ; ++i) *i = typename RR::value_type();
    return r;
  }

  static inline range make_erange(R r)
  {
    return range( r.end() , r.end() );
  }

  static inline difference_type distance( R r )
  {
    return r.distance();
  }
};


};

#endif
