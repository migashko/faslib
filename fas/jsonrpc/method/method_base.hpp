#ifndef FAS_JSONRPC_METHOD_METHOD_BASE_HPP
#define FAS_JSONRPC_METHOD_METHOD_BASE_HPP

#include <stdexcept>
#include <fas/jsonrpc/method/tags.hpp>
#include <fas/jsonrpc/method/local/request/tags.hpp>
#include <fas/jsonrpc/method/local/result/tags.hpp>
#include <fas/jsonrpc/method/local/error/tags.hpp>
#include <fas/jsonrpc/error_code.hpp>

namespace fas{ namespace jsonrpc{

template<typename A1, typename A2 = ::fas::aspect<> >
class method_base
  : public aspect_class<A1, A2>
{
public:
  typedef aspect_class<A1, A2> super;
  typedef typename super::aspect aspect;

  typedef typename aspect::template advice_cast<_context_>::type context_type;

  std::string name() const
  {
    return super::get_aspect().template get<_name_>();
  }

///-> jsonrpc interface

  template<typename T, typename M, typename R>
  bool operator() (T& t, M& m, R r) const
  {
    return this->get_aspect().template get<_name_>()(t, m, r);
  }

  /*
  template<typename R>
  bool check_name(R r) const
  {
    return super::get_aspect().template get<_name_>().check(r);
  }
  */
  
  /*
  template<typename T>
  void invoke_notify(T& t, const notify_value_type& v) 
  {
    // перекинуть в _invoke_notify(t, tm)
    super::get_aspect().template get<_notify_handler_>()(t, *this, v); 
  }
  */

  /*
  template<typename T, typename R>
  void process_notify(T& t, R r) 
  {
    super::get_aspect().template get<_parse_notify_>()(t, *this, r);
  }

  template<typename T, typename R>
  void process_request(T& t, R r, int id) 
  {
    super::get_aspect().template get<_parse_request_>()(t, *this, r, id); 
  }
  */

  template<typename T,typename M, typename V>
  bool result(T& t, M& m, const V& result, int id)
  {
    return super::get_aspect().template get< local::_request_result_ >()(t, m, result, id);
  }

  template<typename T,typename M, typename V>
  bool notify(T& t, M& m, const V& params)
  {
    // super::get_aspect().template get<_send_notify_>()(t, m, params);
    return false;
  }

  template<typename T,typename M, typename V>
  int request(T& t, M& m, const V& params)
  {
    // return super::get_aspect().template get<_send_request_>()(t, m, params);
    return false;
  }

  template<typename T,typename M, typename V>
  bool error(T& t, M& m, const V& message, int id)
  {
    return super::get_aspect().template get< local::_request_error_ >()(t, m, message, id);
  }

  template<typename T,typename M>
  bool error(T& t, M& m, int code, const std::string& message, int id)
  {
    return super::get_aspect().template get< local::_request_error_ >()(t, m, code, message, id);
  }

  template<typename T,typename M>
  bool error(T& t, M& m, error_code::type code, int id)
  {
     return super::get_aspect().template get< local::_request_error_ >()(t, m, code, id);
  }

///<- jsonrpc interface

/// Для удобства 

/*
  notify_handler_type& notify_handler() 
  {
    return super::get_aspect().template get<_notify_>(); 
  }
  
  const notify_handler_type& notify_handler() const  
  {
    return super::get_aspect().template get<_notify_>();
  }
  */

  context_type& context() 
  {
    return super::get_aspect().template get<_context_>();
  }
  
  const context_type& context() const  
  {
    return super::get_aspect().template get<_context_>();
  }

};

}}

#endif
