#ifndef FAS_JSONRPC_INVOKE_REMOTE_PROCESS_INCOMING_HPP
#define FAS_JSONRPC_INVOKE_REMOTE_PROCESS_INCOMING_HPP

#include <fas/jsonrpc/error/tags.hpp>
#include <fas/jsonrpc/invoke/tags.hpp>

namespace fas{ namespace jsonrpc{

struct ad_process_incoming
{
  template<typename T, typename R>
  R operator()( T& t, R r)
  {
    if (!r) return r;

    // TODO: обертка с обработкой исключений всего диапазона
    typedef typename T::aspect::template advice_cast<_parser_>::type parser;
    parser p;
    
    r = p.parse_space(r);

    if ( !p )
      t.get_aspect().template get<_parsing_error_>()(t);

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
