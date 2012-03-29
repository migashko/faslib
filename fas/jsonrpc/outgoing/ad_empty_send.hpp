#ifndef FAS_JSONRPC_OUTGOING_AD_EMPTY_SEND_HPP
#define FAS_JSONRPC_OUTGOING_AD_EMPTY_SEND_HPP

#include <vector>
#include <fas/range/range.hpp>
#include <fas/typemanip/type2type.hpp>

#include <fas/jsonrpc/json/tags.hpp>

namespace fas{ namespace jsonrpc{

struct ad_empty_send
{
  template<typename T>
  bool operator() (T& t)
  {
    typedef typename T::aspect::template advice_cast< _buffer_ >::type buffer_type;
    return _send( t, type2type<buffer_type>() );
  }
  
private:
  
  template<typename T, typename B>
  bool _send( T& t, type2type<B> )
  {
    typedef B buffer_type;
    buffer_type& buffer = t.get_aspect().template get<_buffer_>();
    return _output( t, init_range(buffer, true) );
  }

  template<typename T,  typename B, int N>
  bool _send( T& t, type2type<B[N]> )
  {
    typedef random_access_range<B*> range_type;
    typedef B* buffer_type;
    buffer_type buffer = t.get_aspect().template get<_buffer_>();
    return _output( t, range_type(buffer, buffer + N) );
  }

  template<typename T, typename B>
  bool _send( T& t, type2type<B*> )
  {
    typedef B* buffer_type;
    buffer_type buffer = t.get_aspect().template get<_buffer_>();

    return _output( t,  buffer );
  }

  template<typename T, typename R>
  bool _output(T& t, R r)
  {
    t.get_aspect().template get< _empty_output_ >()( t, r );
    return true;
  }

};

}}

#endif
