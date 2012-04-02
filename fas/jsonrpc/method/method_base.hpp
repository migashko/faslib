#ifndef FAS_JSONRPC_METHOD_METHOD_BASE_HPP
#define FAS_JSONRPC_METHOD_METHOD_BASE_HPP

#include <stdexcept>

#include <fas/jsonrpc/method/tags.hpp>
//#include <fas/jsonrpc/method/local/request/tags.hpp>
#include <fas/jsonrpc/method/local/notify/tags.hpp>
#include <fas/jsonrpc/method/local/result/tags.hpp>
#include <fas/jsonrpc/method/local/request/tags.hpp>
#include <fas/jsonrpc/method/local/error/tags.hpp>

#include <fas/jsonrpc/method/remote/notify/tags.hpp>
#include <fas/jsonrpc/method/remote/request/tags.hpp>
#include <fas/jsonrpc/method/remote/result/tags.hpp>
#include <fas/jsonrpc/method/remote/error/tags.hpp>

#include <fas/jsonrpc/error_code.hpp>
#include <fas/jsonrpc/types.hpp>

namespace fas{ namespace jsonrpc{

template<typename A1, typename A2 = ::fas::aspect<> >
class method_base
  : public aspect_class<A1, A2>
{
public:
  typedef aspect_class<A1, A2> super;
  typedef typename super::aspect aspect;

  typedef typename aspect::template advice_cast<_context_>::type context_type;
  // typedef typename aspect::template advice_cast<_name_>::type::value_type name_range_type;
  

  std::string name() const
  {
    return super::get_aspect().template get<_name_>();
  }

///-> jsonrpc interface

// #warning TODO: сдеать R operator() (T& t, M& m) const а проверку имени вынести в invoke


  /*
  template<typename T>
  typename aspect::template advice_cast<_name_>::type::range_type
  operator()(T&) const
  {
    return super::get_aspect().template get<_name_>()();
  }
  */


  /*
  template<typename T, typename M, typename R>
  bool operator() (T& t, M& m, R r) const
  {
    return this->get_aspect().template get<_name_>()(t, m, r);
  }
  */

  template<typename R>
  bool _check_name(R r, false_) const
  {
    return false;
  }

  template<typename R>
  bool check_name(R r, true_) const
  {
    return super::get_aspect().template get<_name_>()(r);
    // return false;
  }
  
  template<typename R>
  bool check_name(R r) const
  {
    typedef typename super::aspect::template has_advice<_name_>::type has_name;
    return _check_name(r, has_name() );
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
  void parse_notify(T& t, R r)
  {
    super::get_aspect().template get< local::_parse_notify_>()(t, *this, r);
  }

  template<typename T, typename R>
  void parse_request(T& t, R r, id_t id)
  {
    super::get_aspect().template get< local::_parse_request_>()(t, *this, r, id); 
  }

  template<typename T, typename R>
  void parse_result(T& t, R r, id_t id)
  {
    super::get_aspect().template get< remote::_parse_result_>()(t, *this, r, id);
  }

  template<typename T, typename R>
  void parse_error(T& t, R r, id_t id)
  {
    super::get_aspect().template get< remote::_parse_error_>()(t, *this, r, id);
  }

  template<typename T,typename M, typename V>
  bool result(T& t, M& m, const V& result, int id)
  {
    return super::get_aspect().template get< local::_result_ >()(t, m, result, id);
  }

  template<typename T,typename M, typename V>
  bool notify(T& t, M& m, const V& params)
  {
    return super::get_aspect().template get< remote::_notify_ >()(t, m, params);
  }

  template<typename T,typename M, typename V>
  id_t request(T& t, M& m, const V& params)
  {
    return super::get_aspect().template get< remote::_request_ >()(t, m, params);
  }

  template<typename T,typename M, typename V>
  bool error(T& t, M& m, const V& error, int id)
  {
    return super::get_aspect().template get< local::_error_ >()(t, m, error, id);
  }

  template<typename T,typename M>
  bool error(T& t, M& m, int code, const std::string& message, int id)
  {
    return super::get_aspect().template get< local::_error_ >()(t, m, code, message, id);
  }

  template<typename T,typename M>
  bool error(T& t, M& m, error_code::type code, int id)
  {
     return super::get_aspect().template get< local::_error_ >()(t, m, code, id);
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
