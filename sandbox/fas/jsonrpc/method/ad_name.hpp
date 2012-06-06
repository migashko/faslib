#ifndef FAS_JSONRPC_METHOD_AD_NAME_HPP
#define FAS_JSONRPC_METHOD_AD_NAME_HPP


#include <fas/range/string_range.hpp>
#include <string>

namespace fas{ namespace jsonrpc{
 
template<typename N>
struct ad_name
{
  typedef N name_type;
  typedef string_range< typename N::value_type > range_type;

  range_type operator()() const
  {
    return range_type( N()() );
  }

  template<typename R>
  bool operator() (R r1) const
  {
    range_type r2 = range_type( N()() );
    for ( ;r1 && r2 && *r1==*r2; ++r1, ++r2 );
    return !r1 && !r2;
  }

  /*
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

  template<typename T, typename M, typename R>
  bool operator() (T&, M&, R name) const
  {
    range_type r = get_range();
    for ( ;name && r && *name==*r; ++name, ++r );
    return !name && !r;  
  }
  */
};

}}

#endif
