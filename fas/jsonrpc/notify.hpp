#ifndef FAS_JSONRPC_NOTIFY_HPP
#define FAS_JSONRPC_NOTIFY_HPP

#include <fas/jsonrpc/tags.hpp>
#include <fas/jsonrpc/ad_name.hpp>
#include <fas/jsonrpc/ad_method_stub.hpp>
//#include <fas/jsonrpc/method_aspect.hpp>
#include <fas/aop/advice.hpp>
#include <fas/aop/aspect.hpp>
#include <fas/aop/definition.hpp>

namespace fas{ namespace jsonrpc{ 
  
/*

namespace metalist
{
  struct invoke_notify;
  struct invoke_request;
  struct invoke_error;
  
  struct call_notify;
  struct call_request;
  struct call_error;
};

typedef ::fas::aspect<
  type_list_n<
    stub<_context_>,
    advice< _deserializer_, empty_type >,
    advice< _serializer_,   empty_type >
  >::type
> method_base_aspect;

template< typename A >
class method_base
  : public aspect_class< A, method_base_aspect >
{
  typedef aspect_class< A, method_base_aspect > super;
public:
  typedef typename super::aspect aspect;
  typedef typename aspect::template advice_cast<_context_>::type context_type;
};

typedef ::fas::aspect<
  type_list_n<
    stub<_context_>
  >::type
> incoming_method_aspect_type;

template<typename A >
class incoming_method
  : public method_base< typename aspect_merge<A, incoming_method_aspect_type >::type >
{
  typedef method_base< typename aspect_merge<A, incoming_method_aspect_type >::type > super;
public:
  typedef typename super::aspect aspect;

  typedef typename aspect::template advice_cast<_deserializer_>::type deserializer_type;
  typedef typename aspect::template advice_cast<_serializer_>::type serializer_type;
};


typedef ::fas::aspect<
  type_list_n<
    stub<_context_>,
    definition<_notify_value_, void*>,
    definition<_notify_json_, ::fas::json::null>,
    advice< _notify_handler_, ad_method_stub >
  >::type
> notify_aspect_type;

template< typename A >
class notify_base
  : public aspect_class< A, notify_aspect_type >
{
  typedef aspect_class< A, notify_aspect_type > super;
public:
  typedef typename super::aspect aspect;
  
  
  // typedef N name_type;
  // typedef H handler_type;
  // typedef V value_type;
  // typedef J json_type;
  

  typedef typename aspect::template advice_cast<_notify_value_>::type value_type;
  typedef typename aspect::template advice_cast<_notify_json_>::type json_type;
  typedef typename aspect::template advice_cast<_notify_handler_>::type handler_type;
  typedef typename aspect::template advice_cast<_context_>::type context_type;
  
  //typedef typename aspect::template advice_cast<_deserializer_>::type deserializer_type;
  //typedef typename aspect::template advice_cast<_serializer_>::type serializer_type;
  
  
  std::string name() const
  {
    return super::get_aspect().template get<_name_>();
  }
  
  template<typename R>
  bool check_name(R r) const
  {
    return super::get_aspect().template get<_name_>().check(r);
  }

  
  template<typename T>
  void invoke_notify(T& t, const value_type& v) { super::get_aspect().template get<_notify_handler_>()(t, v); }

  
  //template<typename T>
  //void invoke_notify(T& t, const value_type& v) const { super::get_aspect().template get<_handler_>()(t, v); }
  

  handler_type& notify_handler() { return super::get_aspect().template get<_notify_handler_>(); }
  const handler_type& notify_handler() const  { return super::get_aspect().template get<_notify_handler_>();}

  // нужен чтобы для независимости от типа обработчка
  
  context_type& context() { return super::get_aspect().template get<_context_>();}
  const context_type& context() const  { return super::get_aspect().template get<_context_>();}

private:
  
};

template< typename N, typename H, typename V, typename J, typename A = ::fas::aspect<> >
struct make_notify_aspect
{
  typedef ::fas::aspect<
    typename type_list_n<
      advice<_name_, ad_name<N> >,
      advice<_notify_handler_, H >,
      definition<_notify_value_, V >,
      definition<_notify_json_, J >
    >::type
  > aspect_type;
  
  typedef typename aspect_merge< aspect_type, A >::type type;
};
*/

template< typename H, typename V, typename J>
struct notify: type_list_n<
      advice<_notify_, H >,
      definition<_notify_value_, V >,
      definition<_notify_json_, J >
    >::type
{};

template< typename H, typename V = ::fas::empty_type, typename J = ::fas::json::null >
struct request: type_list_n<
      advice<_request_, H >,
      definition<_request_value_, V >,
      definition<_request_json_, J >
    >::type
{};

template< typename V, typename J>
struct result: type_list_n<
      definition<_result_value_, V >,
      definition<_result_json_, J >
    >::type
    {};

/*

template< typename N, typename H, typename V, typename J, typename A = ::fas::aspect<> >
class notify
  : public notify_base< typename make_notify_aspect<N, H, V, J, A>::type  >
{
  
};

*/

/*

template<typename H, typename V, typename J>
struct notify_type
{
  typedef H handler;
  typedef V value_type;
  typedef J json_type;
};
  
template<typename H, typename V, typename J>
struct notify
  : advice<_notify_, notify_type<H, V, J> >
{
};
*/
  
}}

#endif
