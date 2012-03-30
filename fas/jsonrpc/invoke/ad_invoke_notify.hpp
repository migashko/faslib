#ifndef FAS_JSONRPC_INVOKE_AD_INVOKE_NOTIFY_HPP
#define FAS_JSONRPC_INVOKE_AD_INVOKE_NOTIFY_HPP

#include <fas/aop/tag.hpp>

#include <fas/jsonrpc/method/local/notify/tags.hpp>
#include <fas/jsonrpc/method/tags.hpp>
#include <fas/jsonrpc/invoke/tags.hpp>


namespace fas{ namespace jsonrpc{

template<typename RN, typename RP>
struct f_notify
{
  RN name;
  RP params;
  
  bool ready;

  f_notify(RN name, RP params)
    : name(name)
    , params(params)
    , ready(false)
  {}

  template<typename T, typename Tg>
  void operator()(T& t, tag<Tg> )
  {
    if (ready) return;

    /*
    if ( !t.get_aspect().template get<Tg>()
           .get_aspect().template get<_name_>()
           .check( name )
       )
      return;
    */

    if ( !t.get_aspect().template get<Tg>()
          ( t, t.get_aspect().template get<Tg>(), name )
           /*.get_aspect().template get<_name_>()
           .check( name )
            */
       )
      return;

    ready = true;

    t.get_aspect().template get<Tg>().parse_notify( t, t.get_aspect().template get<Tg>(), params);
    /*
    t.get_aspect().template get<Tg>()
     .get_aspect().template get< local::_parse_notify_>()
     (
        t,
        t.get_aspect().template get<Tg>(),
        params
     );
     */
  }

  operator bool () const { return ready; }
};


struct ad_invoke_notify
{
  template<typename T, typename RN, typename RP>
  void operator()(T& t, RN name, RP params )
  {
    if ( !t.get_aspect().template getg<_notify_group_>().for_each(t, f_notify<RN, RP>( name, params ) ) )
      t.get_aspect().template get<_notify_not_found_>()(t, name, params);
  }
};


}}

#endif
