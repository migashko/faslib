#ifndef FAS_JSONRPC_INVOKE_AD_INVOKE_REQUEST_HPP
#define FAS_JSONRPC_INVOKE_AD_INVOKE_REQUEST_HPP

#include <fas/jsonrpc/method/tags.hpp>
#include <fas/jsonrpc/method/local/request/tags.hpp>
#include <fas/jsonrpc/invoke/tags.hpp>
#include <fas/jsonrpc/types.hpp>


namespace fas{ namespace jsonrpc{

template<typename RN, typename RP>
struct f_request
{
  RN name;
  RP params;
  id_t id;
  
  bool ready;

  f_request(RN name, RP params, int id)
    : name(name)
    , params(params)
    , id(id)
    , ready(false)
  {}

  template<typename T, typename Tg>
  void operator()(T& t, tag<Tg> )
  {
    if (ready) return;

    if ( t.get_aspect().template get<_check_name_>()( t, tag<Tg>(), name ) )
    {
      ready = true;
      t.get_aspect().template get<Tg>().parse_request( t, params, id);
    }
  }

  operator bool () const { return ready; }
};


struct ad_invoke_request
{
  template<typename T, typename RN, typename RP>
  void operator()(T& t, RN name, RP params, id_t id  )
  {
    if ( !t.get_aspect().template getg<_request_group_>().for_each(t, f_request<RN, RP>( name, params, id ) ) )
      t.get_aspect().template get<_request_not_found_>()(t, name, params, id);
  }
};


}}

#endif
