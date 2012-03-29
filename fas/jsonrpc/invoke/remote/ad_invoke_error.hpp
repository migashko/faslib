#ifndef FAS_JSONRPC_INVOKE_AD_INVOKE_ERROR_HPP
#define FAS_JSONRPC_INVOKE_AD_INVOKE_ERROR_HPP

#include <fas/jsonrpc/method/tags.hpp>
#include <fas/jsonrpc/invoke/tags.hpp>


namespace fas{ namespace jsonrpc{

template<typename RP>
struct f_error
{
  RP error;
  int id;
  
  bool ready;

  f_error(RP error, int id)
    : error(error)
    , id(id)
    , ready(false)
  {}

  template<typename T, typename Tg>
  void operator()(T& t, tag<Tg> )
  {
    if (ready) return;
    
    if ( !t.get_aspect().template get<Tg>()
           .get_aspect().template get<_remote_id_>()
           .has( id )
       )
      return;

    ready = true;

    t.get_aspect().template get<Tg>()
     .get_aspect().template get<_parse_error_>()
     (
        t,
        t.get_aspect().template get<Tg>(),
        error,
        id
     );
  }

  operator bool () const { return ready; }
};

struct ad_invoke_error
{
  template<typename T, typename RP>
  void operator()(T& t, RP error, int id  )
  {
    if ( !t.get_aspect().template getg<_error_group_>().for_each(t, f_error<RP>( name, error, id ) ) )
      t.get_aspect().template get<_error_not_found_>()(t, error, id);
  }
};


}}

#endif
