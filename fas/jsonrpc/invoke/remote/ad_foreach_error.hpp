#ifndef FAS_JSONRPC_INVOKE_FOREACH_ERROR_HPP
#define FAS_JSONRPC_INVOKE_FOREACH_ERROR_HPP

#include <fas/jsonrpc/invoke/remote/tags.hpp>

namespace fas{ namespace jsonrpc{
  
template<typename Obj>
struct f_error
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
           .get_aspect().template get<_remote_id_>()
           .has( obj.id )
       )
      return;
    
    t.get_aspect().template get<Tg>()
     .get_aspect().template get<_parse_error_>()
     (
        t,
        t.get_aspect().template get<Tg>(),
        obj.error_range(),
        obj.id
     );
  }
  
  operator bool () const { return true; }
};


struct ad_foreach_error
{
  template<typename T, typename Obj>
  void operator()(T& t, const Obj& obj )
  {
    if ( t.get_aspect().template get<_remote_id_>().has(obj.id) )
      t.get_aspect().template getg<_error_group_>().for_each(t, f_error<Obj>( obj ) );
    else
      /*Отправить ошибку*/;
  }
};

 
}}

#endif
