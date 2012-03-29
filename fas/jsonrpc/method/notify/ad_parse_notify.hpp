#ifndef FAS_JSONRPC_METHOD_AD_PARSE_NOTIFY_HPP
#define FAS_JSONRPC_METHOD_AD_PARSE_NOTIFY_HPP

#include <fas/jsonrpc/inbound/tags.hpp>
#include <fas/jsonrpc/method/notify/tags.hpp>
#include <fas/adv/ad_aspect_select.hpp>

namespace fas{ namespace jsonrpc{

template<typename V, typename J>
struct ad_parse_notify : V
{
  typedef V super;
  typedef V request_value;
  typedef J request_json;
  
  template<typename T, typename M, typename R>
  void operator()(T& t, M& m, R r)
  {
    typedef typename T::aspect::template advice_cast<_deserializer_>::type deserializer;
    typename request_value::value_type value = super::operator()(t);

    deserializer ds;
    ds( request_json(), value, r );

    if ( !ds )
      t.get_aspect().template get<_invalid_request_>()(t);
    else
      m.get_aspect().template get<_notify_handler_>()(t, m, value);

  }
};


}}

#endif
