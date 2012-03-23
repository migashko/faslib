#ifndef FAS_JSONRPC_METHOD_AD_NAME_HPP
#define FAS_JSONRPC_METHOD_AD_NAME_HPP


#include <fas/range/string_range.hpp>
#include <string>

namespace fas{ namespace jsonrpc{
 
template<typename N>
struct ad_name
{
  typedef string_range< typename N::value_type > range_type;
  
  typename N::value_type operator()() const 
  {
    return  N()();
  }

  range_type get_range() const
  {
    return range_type( N()() );
  }

  operator std::string() const 
  {
    range_type r = get_range();
    return std::string( r.begin(), r.end() );
  }

  template<typename R>
  bool check(R r1) const
  {
    range_type r2 = get_range();
    for ( ;r1 && r2 && *r1==*r2; ++r1, ++r2 );

    return !r1 && !r2;  
  }
};

}}

#endif
