#ifndef FAS_SERIALIZATION_JSON_RPC_METHOD_HPP
#define FAS_SERIALIZATION_JSON_RPC_METHOD_HPP

#include <fas/aop/aspect.hpp>
#include <fas/aop/advice.hpp>
#include <fas/aop/aspect_class.hpp>
#include <fas/type_list/type_list_n.hpp>
#include <fas/typemanip/some_type.hpp>
#include <fas/serialization/json/meta/tstring.hpp>
#include <fas/serialization/json/rpc/response_object.hpp>
#include <fas/serialization/json/rpc/response_object_json.hpp>

#include <string>
#include <iostream>
namespace fas{ namespace json{ namespace rpc{ namespace method{

  /*
struct _name_;
struct _deserializer_;
struct _serializer_;

// value_json контейнеры	
struct _invoke_request_;
struct _invoke_response_;
struct _invoke_notify_;

struct _call_request_;
struct _call_response_;
struct _call_notify_;

// Обработчики
struct _request_;
struct _response_;
struct _notify_;
*/

/**
 *         remote                    local             
 *       call_request       ->     invoke_request
 *       invoke_response    <-     call_response
 *       call_notify        ->     invoke_notify
 * 
 */

/*
template<typename N>
struct name
  : advice<_name_, tstring<N> > 
{
};


template<typename V, typename J>
struct value_json
{
  typedef V value_type;
  typedef J json_type;
  
  template<typename T>
  void clear(T&) {
    _value = value_type();
  }
  
  value_type& value() {return _value;}
  const value_type& value() const {return _value;}
  
  json_type json() const { return json_type();}
private:
  value_type _value;
};

template<typename VJ  >
struct invoke_request
  : advice<_invoke_request_, VJ > 
{
};

template<typename VJ >
struct invoke_response
  : advice<_invoke_response_, VJ > 
{
};

template<typename VJ >
struct call_request
  : advice<_call_request_, VJ > 
{
};

template<typename VJ >
struct call_response
  : advice<_call_response_, VJ > 
{
};

template<typename VJ  >
struct call_notify
  : advice<_call_notify_, VJ > 
{
};

template<typename VJ >
struct invoke_notify
  : advice<_invoke_notify_, VJ > 
{
};

template<typename H>
struct request
  : advice<_request_, H > 
{
  //typedef H handler;
};

template<typename H>
struct response
  : advice<_response_, H > 
{
  //typedef H handler;
};

template<typename H>
struct notify
  : advice<_notify_, H > 
{
  //typedef H handler;
};



template<typename Tg, typename T1, typename T2, bool>
struct select_advice_impl
{
  typedef typename T1::aspect::template advice_cast<Tg>::type type; 
};

template<typename Tg, typename T1, typename T2>
struct select_advice_impl<Tg, T1, T2, false>
{
  typedef typename T2::template advice_cast<Tg>::type type; 
};

template<typename Tg, typename T1, typename T2>
struct select_advice_helper
{
  enum 
  {
    first = T1::aspect::template has_advice<Tg>::value,
    second = T2::aspect::template has_advice<Tg>::value
  };
  
  // static_check для !first && !second
  typedef typename select_advice_impl<Tg, T1, T2, first>::type type;
};

struct _select_advice_;


struct ad_select_advice
{
  template<typename Tg, typename T1, typename T2>
  typename select_advice_helper<Tg, T1, T2>::type&
  select(T1& t1, T2& t2)
  {
    return _<Tg>(t1, t2, bool2type<select_advice_helper<Tg, T1, T2>::first>() );
  }

  template<typename Tg, typename T1, typename T2>
  typename select_advice_helper<Tg, T1, T2>::type&
  _(T1& t1, T2& t2, bool2type<true>)
  {
    return t1.get_aspect().template get<Tg>();
  }

  template<typename Tg, typename T1, typename T2>
  typename select_advice_helper<Tg, T1, T2>::type&
  _(T1& t1, T2& t2, bool2type<false>)
  {
    return t2.get_aspect().template get<Tg>();
  }
};

struct select_advice_advice
  : advice<_select_advice_, ad_select_advice>
{
  
};

struct _deserialize_strategy_;

struct ad_deserialize_strategy
{
  template<typename Tg, typename T, typename TM,  typename R >
  void deserialize(T& t, TM& tm, R r)
  {
    tm.get_aspect()
      .template get<_select_advice_>()
      .template select<_deserializer_>(tm, t)
    (   
      tm.get_aspect().template get<Tg>().json(),
      tm.get_aspect().template get<Tg>().value(),
      r
    );
  }
};

struct deserialize_strategy_advice
  : advice< _deserialize_strategy_, ad_deserialize_strategy >
{
};

struct _serialize_strategy_;

struct ad_serialize_strategy
{
  template<typename Tg, typename T, typename TM,  typename R >
  void serialize(T& t, TM& tm, R r)
  {
    tm.get_aspect()
      .template get<_select_advice_>()
      .template select<_serializer_>(tm, t)
    (   
      tm.get_aspect().template get<Tg>().json(),
      tm.get_aspect().template get<Tg>().value(),
      r
    );
  }
};

struct serialize_strategy_advice
  : advice< _serialize_strategy_, ad_serialize_strategy >
{
};


struct _invoke_request_handler_;

struct ad_invoke_request_handler
{
  template<typename T, typename TM, typename R>
  void operator()( T& t, TM& tm, R r, int id)
  {
    typedef TM method_type;
    typedef typename method_type::aspect method_aspect;
    
    tm.get_aspect()
      .template get<_deserialize_strategy_>()
      .template deserialize<_invoke_request_>(t, tm, r );
    
    bool ready = tm.get_aspect().template get<_request_>()(t, 
      tm.get_aspect().template get<_invoke_request_>().value(), 
      id,
      tm.get_aspect().template get<_invoke_response_>().value()
    );

    tm.get_aspect()
      .template get<_serialize_strategy_>()
      .template serialize<_invoke_response_>(t, tm, r );
  }
  
  template<typename T, typename TM, typename M, typename V, typename R >
  void _(T& t, TM& tm, M m, V& v, R r, bool2type<true> )
  {
    tm.get_aspect().template get<_deserializer_>()(m, v, r);
  }

  template<typename T, typename TM, typename M, typename V, typename R >
  void _(T& t, TM& tm,  M m, V& v, R r, bool2type<false> )
  {
    t.get_aspect().template get<_deserializer_>()(m, v, r);
  }
};

struct invoke_request_handler_advice
  : advice< _invoke_request_handler_, ad_invoke_request_handler >
{
  
};

struct _response_object_;
struct _response_object_json_;

typedef aspect<
  type_list_n<
    invoke_request_handler_advice,
    select_advice_advice,
    serialize_strategy_advice,
    deserialize_strategy_advice,
    advice<_response_object_, response_object<_> >,
    advice<_response_object_json_, a< response_object_json<_1, _2, _3> >  >
  >::type
> method_aspect_type;

struct method_aspect: method_aspect_type { };
  
template<typename A = aspect<> >
class method
  : public aspect_class<A, method_aspect>
{
public:
  typedef aspect_class<A, method_aspect> super;
  typedef typename super::aspect aspect;
  typedef typename aspect::template advice_cast<_name_>::type name_type;
  
  typedef typename aspect::template advice_cast<_response_object_>::type response_object_type;
  typedef typename aspect::template advice_cast<_response_object_json_>::type response_object_json_type;
  typedef typename aspect::template advice_cast<_invoke_response_>::type invoke_response_type;
  
  typedef typename apply<response_object_type, typename invoke_response_type::value_type>::type response_object;
  typedef typename apply<response_object_json_type, response_object, typename invoke_response_type::value_type, typename invoke_response_type::json_type>::type::type response_object_json;
  

  std::string name() const
  {
    typename name_type::range_type r = this->get_aspect().template get<_name_>().get_range();
    return std::string(r.begin(), r.end());
  }
  
  template<typename T, typename R>
  void invoke_request(T& t, R params, int id)
  {
    response_object ro;
    this->get_aspect().template get<_invoke_request_handler_>()(t, *this, params, id);
    response_object_json roj;
    
    std::cout << "--------------" << std::endl;
    this->get_aspect().template get<_serializer_>()(roj, ro, ( std::ostreambuf_iterator<char>(std::cout) ) );
    std::cout << "--------------" << std::endl;
  }
  

};
*/
  
}}}}

#endif
