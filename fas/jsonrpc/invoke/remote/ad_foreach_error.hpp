#ifndef FAS_JSONRPC_INVOKE_FOREACH_ERROR_HPP
#define FAS_JSONRPC_INVOKE_FOREACH_ERROR_HPP

namespace fas{ namespace jsonrpc{
  
template<typename Obj>
struct f_error
{
  const Obj& obj;
  
  f_error(const Obj& obj)
    : obj(obj)
  {}
  
  template<typename T, typename Tg>
  void operator()(T& t, tag<Tg> )
  {
    if (ready) return;
    
    if ( !t.get_aspect().template get<Tg>()
           .get_aspect().template get<_ids_>()
           .has( obj.id )
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
    t.get_aspect().template getg<_error_group_>().for_each(t, f_error<Obj>( obj ) );
  }
};

 
}}

#endif
