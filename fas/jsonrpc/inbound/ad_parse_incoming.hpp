#ifndef FAS_JSONRPC_INBOUND_AD_PARSE_INCOMING_HPP
#define FAS_JSONRPC_INBOUND_AD_PARSE_INCOMING_HPP

#include <fas/jsonrpc/inbound/error/tags.hpp>
#include <fas/jsonrpc/inbound/tags.hpp>

#include <fas/jsonrpc/invoke/tags.hpp>
#include <fas/jsonrpc/json/tags.hpp>
#include <fas/jsonrpc/error/tags.hpp>




namespace fas{ namespace jsonrpc{

struct ad_parse_incoming
{
  template<typename T, typename R>
  R operator()( T& t, R r)
  {
    typedef typename T::aspect::template advice_cast<_parser_>::type parser;
    parser p;

    if ( p.is_object(r) )
    {
      r = t.get_aspect().template get<_parse_object_>()(t, r);
    }
    else if ( p.is_array(r) )
    {
      r = t.get_aspect().template get<_parse_array_>()(t, r);
    }
    else
    {
      r = p.parse_value(r);
      if ( p )
        t.get_aspect().template get<_invalid_request_>()(t);
      else
        t.get_aspect().template get<_parse_error_>()(t);
    }
      
    return r;
  }
};

}}

#endif
