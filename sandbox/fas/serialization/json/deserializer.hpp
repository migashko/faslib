#ifndef FAS_SERIALIZATION_JSON_DESERIALIZER_HPP
#define FAS_SERIALIZATION_JSON_DESERIALIZER_HPP

#include <fas/aop/aspect_class.hpp>
#include <fas/serialization/json/deser/aspect.hpp>
#include <fas/serialization/json/parser/aspect.hpp>

namespace fas{ namespace json{

template<typename A = ::fas::aspect<> >
class deserializer
  : public aspect_class<A, typename aspect_merge< deser::aspect, parse::aspect>::type >
{
  typedef aspect_class<A, typename aspect_merge< deser::aspect, parse::aspect>::type > super;
  
public:
  
  typedef typename super::aspect aspect;

  operator bool () const
  {
    return !super::get_aspect().template get<_except_>();
  }

  
  template<typename M, typename V, typename R>
  R operator()(M m, V& v, R r)
  {
    return deserialize(*this, m, v, r);
  }
  
protected:
  
  template<typename T, typename M, typename V, typename R>
  R deserialize(T& t, M, V& v, R r)
  {
    typedef typename M::deserializer_tag deserializer_tag; 
    return this->get_aspect().template get<deserializer_tag>()(*this, M(), v, r);
  }
  
};

}}

#endif
