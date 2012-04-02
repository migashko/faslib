#ifndef FAS_JSONRPC_INVOKE_AD_CHECK_RANGE_HPP
#define FAS_JSONRPC_INVOKE_AD_CHECK_RANGE_HPP

namespace fas{ namespace jsonrpc{ 

struct ad_check_range
{
  template<typename T, typename R1, typename R2>
  bool operator() (T&, R1 r1, R2 r2) const
  {
    for ( ;r1 && r2 && *r1==*r2; ++r1, ++r2 );
    return !r1 && !r2;
  }
};

}}

#endif
