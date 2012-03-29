#ifndef FAS_JSONRPC_INVOKE_AD_INVOKE_RESULT_HPP
#define FAS_JSONRPC_INVOKE_AD_INVOKE_RESULT_HPP

#include <fas/jsonrpc/method/tags.hpp>
#include <fas/jsonrpc/invoke/tags.hpp>


namespace fas{ namespace jsonrpc{

template<typename RP>
struct f_result
{
  RP result;
  int id;
  
  bool ready;

  f_result(RP result, int id)
    : result(result)
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
     .get_aspect().template get<_parse_result_>()
     (
        t,
        t.get_aspect().template get<Tg>(),
        result,
        id
     );
  }

  operator bool () const { return ready; }
};


struct ad_invoke_result
{
  
  template<typename T, typename RP>
  void operator()(T& t, RP result, int id  )
  {
    if ( !t.get_aspect().template getg<_result_group_>().for_each(t, f_result<RP>( result, id ) ) )
      t.get_aspect().template get<_result_not_found_>()(t, result, id);
  }
  
};


}}

#endif
