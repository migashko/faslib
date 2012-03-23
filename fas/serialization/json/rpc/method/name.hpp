#ifndef FAS_SERIALIZATION_JSON_RPC_METHOD_NAME_HPP
#define FAS_SERIALIZATION_JSON_RPC_METHOD_NAME_HPP

#include <fas/serialization/json/rpc/method/tags.hpp>
#include <fas/serialization/json/meta/tstring.hpp>
#include <string>

namespace fas{ namespace json{ namespace rpc{ namespace method{
 
template<typename N>
struct ad_name: tstring<N>
{
  typedef tstring<N> super;
  typedef typename super::range_type range_type;

  operator std::string() const 
  {
    range_type r = super::get_range();
    return std::string( r.begin(), r.end() );
  }
  
  template<typename R>
  bool check(R r1) const
  {
    range_type r2 = super::get_range();
    for ( ;r1 && r2 && *r1==*r2; ++r1, ++r2 );

    return !r1 && !r2;  
  }
};

template<typename N>
struct name
  : advice<_name_, ad_name<N> > 
{
};

  
}}}}

#endif
