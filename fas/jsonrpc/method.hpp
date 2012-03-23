#ifndef FAS_JSONRPC_METHOD_HPP
#define FAS_JSONRPC_METHOD_HPP

#include <fas/jsonrpc/tags.hpp>
#include <fas/jsonrpc/method_aspect.hpp>


#include <stdexcept>

namespace fas{ namespace jsonrpc{

template<typename A1, typename A2 = ::fas::aspect<> >
class method_base
  : public aspect_class<A1, A2>
{
public:
  typedef aspect_class<A1, A2> super;
  typedef typename super::aspect aspect;

  typedef typename aspect::template advice_cast<_notify_>::type notify_handler_type;
  typedef typename aspect::template advice_cast<_notify_value_>::type notify_value_type;
  typedef typename aspect::template advice_cast<_notify_json_>::type notify_json_type;

  typedef typename aspect::template advice_cast<_request_>::type request_handler_type;
  typedef typename aspect::template advice_cast<_request_value_>::type request_value_type;
  typedef typename aspect::template advice_cast<_request_json_>::type request_json_type;
  typedef typename aspect::template advice_cast<_result_value_>::type result_value_type;
  typedef typename aspect::template advice_cast<_result_json_>::type result_json_type;

  typedef typename aspect::template advice_cast<_context_>::type context_type;

  std::string name() const
  {
    return super::get_aspect().template get<_name_>();
  }

///-> jsonrpc interface

  template<typename R>
  bool check_name(R r) const
  {
    return super::get_aspect().template get<_name_>().check(r);
  }
  
  /*
  template<typename T>
  void invoke_notify(T& t, const notify_value_type& v) 
  {
    // перекинуть в _invoke_notify(t, tm)
    super::get_aspect().template get<_notify_handler_>()(t, *this, v); 
  }
  */

  template<typename T, typename R>
  void process_notify(T& t, R r) 
  {
    super::get_aspect().template get<_process_notify_>()(t, *this, r); 
  }

  template<typename T, typename R>
  void process_request(T& t, R r, int id) 
  {
    super::get_aspect().template get<_process_request_>()(t, *this, r, id); 
  }

  template<typename T>
  void response(T& t, const result_value_type& result, int id)
  {
    super::get_aspect().template get<_process_response_>()(t, *this, result, id); 
  }
  
///<- jsonrpc interface

/// Для удобства 

  notify_handler_type& notify_handler() 
  {
    return super::get_aspect().template get<_notify_>(); 
  }
  
  const notify_handler_type& notify_handler() const  
  {
    return super::get_aspect().template get<_notify_>();
  }

  context_type& context() 
  {
    return super::get_aspect().template get<_context_>();
  }
  
  const context_type& context() const  
  {
    return super::get_aspect().template get<_context_>();
  }

};

template<typename A = ::fas::aspect<> >
class method:
  public method_base<A, method_aspect>
{
  typedef method_base<A, method_aspect> super;
};

  /*
template<typename A1, typename A2 = ::fas::aspect<> >
class method_base
  : public aspect_class<A1, A2>
{
public:
  typedef aspect_class<A1, A2> super;
  typedef typename super::aspect aspect;
  
  std::string name() const
  {
    return super::get_aspect().template get<_name_>();
  }
  
  template<typename R>
  bool check_name(R r) const
  {
    return super::get_aspect().template get<_name_>().check(r);
  }

  bool check_id(int id) const
  {
    return this->get_aspect().template get<_call_ids_>().has(id);
  }

  template<typename T, typename R>
  void invoke_request(T& t, R r, int id )
  {
    this->get_aspect().template get< _invoke_request_handler_ >()(t, *this, r, id);
  }

  template<typename T, typename R>
  void invoke_notify(T& t, R r)
  {
    this->get_aspect().template get< _invoke_notify_handler_ >()(t, *this, r);
  }

  template<typename T, typename R>
  void invoke_result(T& t, R r, int id )
  {
    this->get_aspect().template get< _invoke_result_handler_ >()(t, *this, r, id);
  }

  template<typename T, typename R>
  void invoke_error(T& t, R r, int id )
  {
    this->get_aspect().template get< _invoke_error_handler_ >()(t, *this, r, id);
  }

  template<typename T, typename R>
  void invoke_error(T& t, R r )
  {
    this->get_aspect().template get< _invoke_error_handler_ >()(t, *this, r);
  }

  template<typename T, typename V>
  void request(T& t, const V& params, int id)
  {
    throw std::logic_error("not impl");
  }

  template<typename T, typename V>
  void response(T& t, const V& result, int id)
  {
    throw std::logic_error("not impl");
  }

  template<typename T, typename V>
  void notify(T& t, const V& params)
  {
    throw std::logic_error("not impl");
  }

  template<typename T, typename V>
  void error(T& t, const V& err, int id)
  {
    throw std::logic_error("not impl");
  }

  template<typename T, typename V>
  void error(T& t, const V& err)
  {
    throw std::logic_error("not impl");
  }

};
  */
}}

#endif
