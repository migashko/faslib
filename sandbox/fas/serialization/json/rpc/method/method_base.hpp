#ifndef FAS_SERIALIZATION_JSON_RPC_METHOD_METHOD_BASE_HPP
#define FAS_SERIALIZATION_JSON_RPC_METHOD_METHOD_BASE_HPP

#include <fas/aop/aspect.hpp>
#include <fas/aop/aspect_class.hpp>
#include <fas/serialization/json/rpc/method/tags.hpp>

namespace fas{ namespace json{ namespace rpc{ namespace method{

  
template<typename A1, typename A2 = ::fas::aspect<> >
class method_base
  : public aspect_class<A1, A2>
{
public:
  std::string name() const
  {
    return this->get_aspect().template get<_name_>();
  }
  
  template<typename R>
  bool check_name(R r) const
  {
    return this->get_aspect().template get<_name_>().check(r);
  }

  bool check_id(int id) const
  {
    return this->get_aspect().template get<_id_>().has(id);
  }

  template<typename R>
  void invoke_request(R r, int id )
  {
    this->get_aspect().template get< _invoke_request_handler_ >()(*this, *this, r, id);
  }
  
  template<typename T, typename R>
  void invoke_request(T& t, R r, int id )
  {
    this->get_aspect().template get< _invoke_request_handler_ >()(t, *this, r, id);
  }

  template<typename T, typename R>
  void invoke_notify(T& t, R r, int id )
  {
    throw std::logic_error("TODO: impl");
  }

  template<typename T, typename R>
  void invoke_response(T& t, R r, int id )
  {
    throw std::logic_error("TODO: impl");
  }
  
  template<typename T, typename RO>
  void response(T& t, const RO& ro, int id)
  {
    this->get_aspect().template get<_invoke_response_>().value() = ro;
    this->get_aspect().template get<_invoke_response_handler_>()(t, *this, id);
  }
  
};
  
}}}}

#endif
