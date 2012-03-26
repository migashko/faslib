#ifndef FAS_JSONRPC_OUTGOING_AD_SEND_HPP
#define FAS_JSONRPC_OUTGOING_AD_SEND_HPP

#include <vector>
#include <fas/range/range.hpp>
#include <fas/typemanip/type2type.hpp>

#include <fas/jsonrpc/json/tags.hpp>

namespace fas{ namespace jsonrpc{

struct ad_send
{
  template<typename T, typename M, typename V>
  void operator() (T& t, M, const V& value)
  {
    typedef typename T::aspect::template advice_cast< _buffer_ >::type buffer_type;
    
    if ( !_send(t, M(), value, type2type<buffer_type>() ) )
      throw ;
    /*
    typedef typename range_traits< buffer_type >::init_range init_range_type;
    typedef typename range_traits< buffer_type >::range range_type;
    
    buffer_type& buffer = t.get_aspect().template get<_buffer_>();

    serializer s;
    s( M(), value, init_range(buffer, true) );
    
    if ( s )
      t.get_aspect().template get<_output_>()( t, range( buffer ) );
    else
      throw 
      */
      /* недостаточно буфера */;
  }
  
private:
  
  template<typename T, typename M, typename V, typename B>
  bool _send( T& t, M, const V& value, type2type<B> )
  {
    typedef typename T::aspect::template advice_cast< _serializer_ >::type serializer;    
    typedef B buffer_type;
    
    buffer_type& buffer = t.get_aspect().template get<_buffer_>();
    
    serializer s;
    s( M(), value, init_range(buffer, true) );
    
    
    if ( s )
      t.get_aspect().template get<_output_>()( t, range( buffer ) );
    else
      return false;
    return true;
  }
  

  template<typename T, typename M, typename V, typename B, int N>
  bool _send( T& t, M, const V& value, type2type<B[N]> )
  {
    typedef typename T::aspect::template advice_cast< _serializer_ >::type serializer;    
    typedef random_access_range<B*> range_type;
    typedef B* buffer_type;
    
    buffer_type buffer = t.get_aspect().template get<_buffer_>();
    serializer s;
    range_type r = s( M(), value, range_type(buffer, buffer + N) );
    
    if ( s )
      t.get_aspect().template get<_output_>()( t, range_type( buffer, r.begin() ) );
    else
      return false;
    return true;
  }

  template<typename T, typename M, typename V, typename B>
  bool _send( T& t, M, const V& value, type2type<B*> )
  {
    typedef typename T::aspect::template advice_cast< _serializer_ >::type serializer;    
    typedef random_access_range<B*> range_type;
    
    B* beg = t.get_aspect().template get<_buffer_>();
    
    serializer s;
    B* end = s( M(), value, beg );
    
    if ( s )
      t.get_aspect().template get<_output_>()( t, range_type( beg, end ) );
    else
      return false;
    
    return true;
  }

};

}}

#endif
