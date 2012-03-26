#ifndef FAS_JSONRPC_INVOKE_FOREACH_REQUEST_HPP
#define FAS_JSONRPC_INVOKE_FOREACH_REQUEST_HPP

#include <fas/jsonrpc/method/tags.hpp>

namespace fas{ namespace jsonrpc{

template<typename Obj>
struct f_request
{
  const Obj& obj;
  bool ready;

  f_request(const Obj& obj)
    : obj(obj)
    , ready(true)
  {}

  template<typename T, typename Tg>
  void operator()(T& t, tag<Tg> )
  {
    if (ready) return;
    
    if ( !t.get_aspect().template get<Tg>()
           .get_aspect().template get<_name_>()
           .check( obj.name_range() )
       )
      return;

    ready = true;
    
    t.get_aspect().template get<Tg>()
     .get_aspect().template get<_parse_request_>()
     (
        t,
        t.get_aspect().template get<Tg>(),
        obj.params_range(),
        obj.id
     );
  }

  operator bool () const { return ready; }
};


struct ad_foreach_request
{
  template<typename T, typename Obj>
  void operator()(T& t, const Obj& obj )
  {
    if ( !t.get_aspect().template getg<_request_group_>().for_each(t, f_request<Obj>( obj ) ) )
      t.get_aspect().template get<_method_not_found_>()(t, obj.id);
  }
};


}}

#endif
