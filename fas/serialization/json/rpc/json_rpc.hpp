#ifndef FAS_SERIALIZATION_JSON_RPC_JSON_RPC_HPP
#define FAS_SERIALIZATION_JSON_RPC_JSON_RPC_HPP

#include <fas/serialization/json/rpc/aspect.hpp>

#include <fas/aop/aspect.hpp>
#include <fas/aop/aspect_class.hpp>
#include <fas/aop/advice_cast.hpp>


namespace fas{ namespace json{ namespace rpc{

/*
Out of common sense : 
1. Correct JSON (if not => PARSE ERROR) 
2. Correct JSON-RPC (if not => INVALID REQUEST) 
3. Method Match (if not => INVALID METHOD) 
4. Execution 
5. Result (Only for full requests) 
 */
  
template<typename A1 = ::fas::aspect<>, typename A2 = ::fas::aspect<> >
class json_rpc_base
  :  public ::fas::aspect_class< A1, A2 >
{
public:
  typedef ::fas::aspect_class< A1, A2 > super;
  typedef typename super::aspect aspect;
  typedef typename aspect::template advice_cast<_outgoing_buffer_>::type buffer_type;
  
  template<typename T, typename R>
  void operator()(T& t, R r)
  {
    this->_exec(t, r);
  }

  template<typename R>
  void operator()(R r)
  {
    this->_exec(*this, r);
  }
  
  template<typename R>
  void exec(R r)
  {
    this->_exec(*this, r);
  }
  
  buffer_type& buffer() { return super::get_aspect().template get<_outgoing_buffer_>(); }
  
  const buffer_type& buffer() const { return super::get_aspect().template get<_outgoing_buffer_>(); }

  template<typename T>
  typename advice_cast<_outgoing_buffer_, typename T::aspect >::type& buffer(T& t) { return t.get_aspect().template get<_outgoing_buffer_>(); }
  
  template<typename T>
  typename advice_cast<_outgoing_buffer_, typename T::aspect >::type& buffer(T& t) const { return t.get_aspect().template get<_outgoing_buffer_>(); }

protected:
  
  template<typename T, typename R>
  R _exec(T& t, R r)
  {
    t.get_aspect().template get<_invoke_exec_>()(t, r);
    
  }

};

  
  
template<typename A = ::fas::aspect<> >
class json_rpc
  :  public json_rpc_base< A, ::fas::json::rpc::aspect >
{
  
  typedef json_rpc_base< A, ::fas::json::rpc::aspect > super;
  typedef typename super::aspect aspect;
  
public:
  
  template<typename T, typename R>
  void operator()(T& t, R r)
  {
    super::_exec(t, r);
  }

  template<typename R>
  void operator()(R r)
  {
    super::_exec(*this, r);
  }
  
  template<typename R>
  void exec(R r)
  {
    super::_exec(*this, r);
  }
  

};
  
}}}

#endif
