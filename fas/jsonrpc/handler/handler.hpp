#ifndef FAS_JSONRPC_HANDLER_HANDLER_HPP
#define FAS_JSONRPC_HANDLER_HANDLER_HPP

#include <fas/aop/aspect.hpp>
#include <fas/aop/advice.hpp>
#include <fas/type_list/type_list_n.hpp>

#include <fas/jsonrpc/aspect.hpp>


namespace fas{ namespace jsonrpc{

typedef type_list_n<
  aspect
>::type handler_advice_list;
  
typedef ::fas::aspect< handler_advice_list > handler_aspect_type;

struct handler_aspect: handler_aspect_type {};
  
template<typename A1 = ::fas::aspect<>, typename A2 = handler_aspect >
class handler
  : public aspect_class<A1, A2 >
{
public:
  template<typename R>
  R operator () (R r)
  {
    return this->get_aspect().template get<_process_incoming_>()( *this, r);
  }
  
};

}}

#endif
