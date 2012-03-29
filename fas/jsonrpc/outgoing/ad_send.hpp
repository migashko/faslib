#ifndef FAS_JSONRPC_OUTGOING_AD_SEND_HPP
#define FAS_JSONRPC_OUTGOING_AD_SEND_HPP

#include <vector>
#include <fas/range/range.hpp>
#include <fas/typemanip/type2type.hpp>

#include <fas/jsonrpc/json/tags.hpp>

namespace fas{ namespace jsonrpc{

struct ad_send
{
  template<typename T, typename J, typename V>
  bool operator() (T& t, J, const V& value)
  {
    typedef typename T::aspect::template advice_cast< _buffer_ >::type buffer_type;
    
    return _send( t, J(), value, type2type<buffer_type>() );
  }
  
private:
  
  template<typename T, typename J, typename V, typename B>
  bool _send( T& t, J, const V& value, type2type<B> )
  {
    typedef B buffer_type;
    buffer_type& buffer = t.get_aspect().template get<_buffer_>();
    return _output( t, J(), value, init_range(buffer, true) );
  }

  template<typename T, typename J, typename V, typename B, int N>
  bool _send( T& t, J, const V& value, type2type<B[N]> )
  {
    typedef random_access_range<B*> range_type;
    typedef B* buffer_type;

    buffer_type buffer = t.get_aspect().template get<_buffer_>();
    return _output( t, J(), value, range_type(buffer, buffer + N) );
  }

  template<typename T, typename J, typename V, typename B>
  bool _send( T& t, J, const V& value, type2type<B*> )
  {
    typedef B* buffer_type;
    buffer_type buffer = t.get_aspect().template get<_buffer_>();

    return _output( t, J(), value, buffer );
  }

  template<typename T, typename J, typename V, typename R>
  bool _output(T& t, J, const V& value, R r)
  {
    typedef typename T::aspect::template advice_cast< _serializer_ >::type serializer;
    serializer s;
    R rr = s( J(), value, r );

    if ( s )
    {
      t.get_aspect().template get< _output_ >()( t, rr );
      t.get_aspect().template get< _empty_send_ >()( t);
    }
    else
      t.get_aspect().template get< _send_failed_ >()( t, J(), value, r, s.exception() );

    

    return (bool) s;
  }

};

}}

#endif
