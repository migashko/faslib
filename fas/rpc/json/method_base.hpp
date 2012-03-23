#ifndef FAS_RPC_JSON_METHOD_BASE_HPP
#define FAS_RPC_JSON_METHOD_BASE_HPP

#include <fas/rpc/json/tags.hpp>

#include <stdexcept>

namespace fas{ namespace rpc{ namespace json{

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
  
}}}

#endif
