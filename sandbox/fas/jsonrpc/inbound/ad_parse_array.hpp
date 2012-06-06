#ifndef FAS_JSONRPC_INBOUND_AD_PARSE_ARRAY_HPP
#define FAS_JSONRPC_INBOUND_AD_PARSE_ARRAY_HPP

#include <fas/jsonrpc/inbound/error/tags.hpp>
#include <fas/jsonrpc/inbound/tags.hpp>

namespace fas{ namespace jsonrpc{
  

struct ad_parse_array
{
  template<typename T, typename R>
  R operator()(T& t, R r )
  {
    typedef typename T::aspect::template advice_cast<_parser_>::type parser;
    parser p;

    r = p.parse_array(r);
    
    if ( p )
      t.get_aspect().template get<_invalid_request_>()(t);
    else
      t.get_aspect().template get<_parse_error_>()(t);

    return r;
  }
};

}}

#endif
