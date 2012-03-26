#ifndef FAS_JSONRPC_INVOKE_REMOTE_PARSE_INCOMING_HPP
#define FAS_JSONRPC_INVOKE_REMOTE_PARSE_INCOMING_HPP

#include <fas/jsonrpc/invoke/tags.hpp>
#include <fas/jsonrpc/aspect.hpp>


/*
#include <fas/jsonrpc/raw_object.hpp>
#include <fas/jsonrpc/raw_object_json.hpp>
*/

#include <fas/aop/aspect.hpp>
#include <fas/aop/advice.hpp>
#include <fas/type_list/type_list_n.hpp>

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
        t.get_aspect().template get<_parsing_error_>()(t);
    }
      
    return r;
  }
};

}}

#endif
