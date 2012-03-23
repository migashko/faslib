#ifndef FAS_SERIALIZATION_JSON_RPC_METHOD_AD_RESPONSE_BUFFER_HPP
#define FAS_SERIALIZATION_JSON_RPC_METHOD_AD_RESPONSE_BUFFER_HPP

#include <fas/aop/advice_cast.hpp>
#include <fas/serialization/json/rpc/method/tags.hpp>

namespace fas{ namespace json{ namespace rpc{ namespace method{
  
namespace detail
{
  template<typename T, typename TM, bool F>
  struct outgoing_buffer_helper;

  template<typename T, typename TM>
  struct outgoing_buffer_helper<T, TM, true>
  {
    typedef typename TM::aspect::template advice_cast<_outgoing_buffer_>::type type;
  };

  template<typename T, typename TM>
  struct outgoing_buffer_helper<T, TM, false>
  {
    typedef typename T::aspect::template advice_cast<_outgoing_buffer_>::type type;
  };

}

struct ad_response_buffer
{
  template<typename T, typename TM>
  struct outgoing_buffer
  {
    enum { has_method_buffer = TM::aspect::template has_advice<_outgoing_buffer_>::value };
    typedef typename detail::outgoing_buffer_helper<T, TM, has_method_buffer>::type type;
  };
  
  template<typename T, typename TM>
  typename outgoing_buffer<T, TM>::type& operator() (T& t, TM& tm)
  {
    return _(t, tm, bool_< outgoing_buffer<T, TM>::has_method_buffer>() );
  }
  
private:
  template<typename T, typename TM>
  typename outgoing_buffer<T, TM>::type& _(T& t, TM& tm, bool_<true> )
  {
    return tm.get_aspect().template get<_outgoing_buffer_>();
  }

  template<typename T, typename TM>
  typename outgoing_buffer<T, TM>::type& _(T& t, TM& tm, bool_<false> )
  {
    return t.get_aspect().template get<_outgoing_buffer_>();
  }
};

}}}}

#endif

