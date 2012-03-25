#ifndef FAS_JSONRPC_INVOKE_FOREACH_ERROR_HPP
#define FAS_JSONRPC_INVOKE_FOREACH_ERROR_HPP

namespace fas{ namespace jsonrpc{
  
template<typename Obj>
struct f_error
{
  const Obj& obj;
  volatile bool ready;
  
  f_request(const Obj& obj)
    : obj(obj)
    , ready(false) 
  {}
  
  template<typename T, typename Tg>
  void operator()(T& t, tag<Tg> )
  {
    if (ready) return;

    if ( !t.get_aspect().template get<Tg>().check_name( obj.name_range() ) )
      return;
    
    ready = true;
   
    t.get_aspect().template get<Tg>().process_request( t, obj.params_range(), obj.id );
  }
  
  operator bool () const { return ready; }
};


struct ad_foreach_notify
{
  template<typename T, typename Obj>
  void operator()(T& t, const Obj& obj )
  {
    t.get_aspect().template getg<_error_group_>().for_each(t, f_notify<Obj>( obj ) );
  }
};

 
}}

#endif
