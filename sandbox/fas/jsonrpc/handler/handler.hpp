#ifndef FAS_JSONRPC_HANDLER_HANDLER_HPP
#define FAS_JSONRPC_HANDLER_HANDLER_HPP

#include <string>
#include <fas/jsonrpc/tags.hpp>
#include <fas/jsonrpc/handler/handler_aspect.hpp>


namespace fas{ namespace jsonrpc{
  
template<typename A1 = ::fas::aspect<>, typename A2 = handler_aspect >
class handler_base
  : public aspect_class<A1, A2 >
{
  
public:
  typedef handler_base<A1, A2> self;
  
  template<typename R>
  R operator () (R r)
  {
    return this->get_aspect().template get<_input_>()( *this, r);
  }

  
  self& operator << ( const std::string& value)
  {
    _buffer += value;
    return *this;
  }
  
  
  const std::string& result() const
  {
    return _buffer;
  }

  void clear()
  {
    _buffer.clear();
  }

  template<typename R>
  const std::string& parse( R r)
  {
    _buffer.clear();
    this->get_aspect().template get<_input_>()( *this, r);
    return _buffer;
  }

  template<typename Tg, typename V>
  const std::string& notify(const V& v)
  {
    _buffer.clear();
    this->get_aspect().template get<Tg>().notify(*this, v);
    return _buffer;
  }

  template<typename Tg, typename V>
  const std::string& request(const V& v)
  {
    _buffer.clear();
    this->get_aspect().template get<Tg>().request(*this, v);
    return _buffer;
  }
  
public:
  std::string _buffer;
};

template<typename A1 = ::fas::aspect<> >
class handler:
  public handler_base<A1, handler_aspect>
{
  
};


}}

#endif
