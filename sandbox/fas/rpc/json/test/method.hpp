#ifndef FAS_RPC_JSON_TEST_METHOD_HPP
#define FAS_RPC_JSON_TEST_METHOD_HPP

#include <fas/rpc/json/method.hpp>
#include <fas/rpc/json/test/method/aspect.hpp>

namespace fas{ namespace rpc{ namespace json{ namespace test{

template<typename A = ::fas::aspect<> >
class method
  : public ::fas::rpc::json::method< typename aspect_merge< A, method_aspect>::type >
{
public:
  typedef ::fas::rpc::json::method< typename aspect_merge< A, method_aspect>::type > super;
  typedef typename super::aspect aspect;
  
  template<typename R>
  void invoke_request(R r, int id )
  {
    super::invoke_request(*this, r, id);
  }

  template<typename R>
  void invoke_notify(R r)
  {
    super::invoke_notify(*this, r);
  }

  template<typename R>
  void invoke_result(R r, int id )
  {
    super::invoke_result(*this, r, id);
  }

  template<typename R>
  void invoke_error(R r, int id )
  {
    super::invoke_error(*this, r, id);
  }

  template<typename R>
  void invoke_error(R r)
  {
    super::invoke_error(*this, r);
  }

  template<typename V>
  void request(const V& params, int id)
  {
    super::request(*this, params, id);
  }

  template<typename V>
  void response(const V& result, int id)
  {
    super::response(*this, result, id);
  }

  template<typename V>
  void notify(const V& params)
  {
    super::notify(*this, params);
  }

  template<typename V>
  void error(const V& err, int id)
  {
    super::error(*this, err, id);
  }

  template<typename V>
  void error(const V& err)
  {
    super::error(*this, err);
  }
  
  typename aspect::template advice_cast<_result_buffer_>::type&
  result() { return super::get_aspect().template get<_result_buffer_>(); }

  const typename aspect::template advice_cast<_result_buffer_>::type&
  result() const { return super::get_aspect().template get<_result_buffer_>(); }

};
  
}}}}

#endif
