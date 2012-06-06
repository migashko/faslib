#ifndef FAS_JSONRPC_INVOKE_AD_INVOKE_RESULT_HPP
#define FAS_JSONRPC_INVOKE_AD_INVOKE_RESULT_HPP

#include <fas/jsonrpc/method/tags.hpp>
#include <fas/jsonrpc/invoke/tags.hpp>
#include <fas/jsonrpc/types.hpp>


namespace fas{ namespace jsonrpc{

template<typename RP>
struct f_result
{
  RP result;
  id_t id;
  
  bool ready;

  f_result(RP result, id_t id)
    : result(result)
    , id(id)
    , ready(false)
  {}

  template<typename T, typename Tg>
  void operator()(T& t, tag<Tg> )
  {
    if (ready) return;
    
    if ( !t.get_aspect().template get<Tg>().check_id( id ) )
      return;

    ready = true;

    t.get_aspect().template get<Tg>().parse_result(t, result, id);
  }

  operator bool () const { return ready; }
};


struct ad_invoke_result
{
  
  template<typename T, typename RP>
  void operator()(T& t, RP result, id_t id  )
  {
    if ( !t.get_aspect().template getg<_result_group_>().for_each(t, f_result<RP>( result, id ) ) )
      t.get_aspect().template get<_result_not_found_>()(t, result, id);
  }
  
};


}}

#endif
