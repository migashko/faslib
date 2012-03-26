#ifndef FAS_JSONRPC_INVOKE_FOREACH_RESPONSE_HPP
#define FAS_JSONRPC_INVOKE_FOREACH_RESPONSE_HPP

namespace fas{ namespace jsonrpc{

template<typename Obj>
struct f_response
{
  const Obj& obj;
  bool ready;

  f_error(const Obj& obj)
    : obj(obj)
    , ready(false)
  {}

  template<typename T, typename Tg>
  void operator()(T& t, tag<Tg> )
  {
    if (ready) return;
    
    if ( !t.get_aspect().template get<Tg>()
           .get_aspect().template get<_ids_>()
           .has( obj.id )
      return;

    ready = true;

    t.get_aspect().template get<Tg>()
     .get_aspect().template get<_process_response_>()
     (
        t,
        t.get_aspect().template get<Tg>(),
        obj.result_range(),
        obj.id
     );
  }

  operator bool () const { return ready; }
};


struct ad_foreach_response
{
  template<typename T, typename Obj>
  void operator()(T& t, const Obj& obj )
  {
    t.get_aspect().template getg<_response_group_>().for_each(t, f_response<Obj>( obj ) );
  }
};


}}

#endif
