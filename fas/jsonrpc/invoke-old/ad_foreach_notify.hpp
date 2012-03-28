#ifndef FAS_JSONRPC_INVOKE_FOREACH_NOTIFY_HPP
#define FAS_JSONRPC_INVOKE_FOREACH_NOTIFY_HPP

#include <fas/jsonrpc/method/tags.hpp>


namespace fas{ namespace jsonrpc{

template<typename Obj>
struct f_notify
{
  const Obj& obj;
  bool ready;

  f_notify(const Obj& obj)
    : obj(obj)
    , ready(false)
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
     .get_aspect().template get<_parse_notify_>()
     (
        t,
        t.get_aspect().template get<Tg>(),
        obj.params_range()
     );
  }

  operator bool () const { return ready; }
};


struct ad_foreach_notify
{
  template<typename T, typename Obj>
  void operator()(T& t, const Obj& obj )
  {
    if ( !t.get_aspect().template getg<_notify_group_>().for_each(t, f_notify<Obj>( obj ) ) )
      t.get_aspect().template get<_method_not_found_>()(t);
  }
};


}}

#endif
