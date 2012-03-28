#ifndef FAS_JSONRPC_INBOUND_AD_INBOUND_HPP
#define FAS_JSONRPC_INBOUND_AD_INBOUND_HPP

#include <fas/jsonrpc/inbound/error/tags.hpp>
#include <fas/jsonrpc/inbound/tags.hpp>

namespace fas{ namespace jsonrpc{

struct ad_inbound
{
  template<typename T, typename R>
  R operator()( T& t, R r)
  {
    if (!r) return r;

    typedef typename T::aspect::template advice_cast<_parser_>::type parser;
    parser p;
    
    r = p.parse_space(r);

    if ( !p )
      t.get_aspect().template get<_parse_error_>()(t);

    while( r )
    {
      r = t.get_aspect().template get<_parse_incoming_>()(t, r);

      if ( r )
        r = p.parse_space(r);
    }
    
    return r;
  }
};

}}

#endif
