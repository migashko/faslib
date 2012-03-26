#ifndef FAS_JSONRPC_OUTGOING_AD_SEND_HPP
#define FAS_JSONRPC_OUTGOING_AD_SEND_HPP

#include <vector>
#include <fas/range/range.hpp>


namespace fas{ namespace jsonrpc{

struct ad_send
{
  template<typename T, typename M, typename V>
  void operator() (T& t, M, const V& value)
  {
    typedef typename T::aspect::template advice_cast< _serializer_ >::type  serializer;

    std::vector<char> buffer;

    serializer s;
    s( M(), value, init_range(buffer) );

    t.get_aspect().template get<_output_>()( t, range( buffer ) );
  }
};

}}

#endif
