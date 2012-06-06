#ifndef FAS_JSONRPC_INVOKE_AD_INVOKE_ERROR_HPP
#define FAS_JSONRPC_INVOKE_AD_INVOKE_ERROR_HPP

#include <fas/jsonrpc/method/tags.hpp>
#include <fas/jsonrpc/invoke/tags.hpp>


namespace fas{ namespace jsonrpc{

template<typename RP>
struct f_error
{
  RP error;
  id_t id;
  
  bool ready;

  f_error(RP error, id_t id)
    : error(error)
    , id(id)
    , ready(false)
  {}

  template<typename T, typename Tg>
  void operator()(T& t, tag<Tg> )
  {
    std::cout  << "f_error 1" << std::endl;
    
    if (ready) return;
    
    std::cout  << "f_error 2" << std::endl;
    
    if ( !t.get_aspect().template get<Tg>().check_id(id) )
      return;

    std::cout  << "f_error 3" << std::endl;
    
    ready = true;

    std::cout  << "f_error 4" << std::endl;
    
    t.get_aspect().template get<Tg>().parse_error(t, error, id);

    std::cout  << "f_error 5" << std::endl;
  }

  operator bool () const { return ready; }
};

struct ad_invoke_error
{
  template<typename T, typename RP>
  void operator()(T& t, RP error, id_t id  )
  {
    if ( !t.get_aspect().template getg<_error_group_>().for_each(t, f_error<RP>( error, id ) ) )
      t.get_aspect().template get<_error_not_found_>()(t, error, id);
  }
};


}}

#endif
