#ifndef FAS_JSONRPC_AD_PROCESS_NOTIFY_HPP
#define FAS_JSONRPC_AD_PROCESS_NOTIFY_HPP

#include <fas/jsonrpc/tags.hpp>
#include <fas/adv/ad_aspect_select.hpp>

namespace fas{ namespace jsonrpc{ 

struct ad_process_notify
{
  template<typename T, typename TM, typename R>
  void operator()(T& t, TM& tm, R r)
  {
     std::cout << "void process_notify(T& t, R r) " << std::endl;
    typedef typename switch_by_tag_t<_deserializer_>::template select_t< TM, T >::type::aspect::template advice_cast<_deserializer_>::type deserializer;
    typedef typename TM::notify_value_type notify_value_type;
    typedef typename TM::notify_json_type notify_json_type;

    try
    {
      notify_value_type value;
      deserializer()(notify_json_type(), value, r );
      tm.get_aspect().template get<_notify_handler_>()(t, tm, value); 
    }
    catch(const std::exception& /*e*/)
    {
      // server error
    }
    catch(...)
    {
      // server error
    }
  }
};


}}

#endif
