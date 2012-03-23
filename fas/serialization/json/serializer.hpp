#ifndef FAS_SERIALIZATION_JSON_SERIALIZER_HPP
#define FAS_SERIALIZATION_JSON_SERIALIZER_HPP

#include <fas/aop/aspect_class.hpp>
#include <fas/serialization/json/ser/aspect.hpp>

namespace fas{ namespace json{

template<typename A = ::fas::aspect<> >
class serializer
  : public aspect_class<A, ser::aspect >
{
  typedef aspect_class<A, ser::aspect > super;
public:
  typedef typename super::aspect aspect;
  
  template<typename M, typename V, typename R>
  R operator()(M m, const V& v, R r)
  {
    return serialize(*this, m, v, r);
  }
  
protected:

  template<typename T, typename M, typename V, typename R>
  R serialize(T& t, M, const V& v, R r)
  {
    typedef typename M::serializer_tag serializer_tag; 
    return t.get_aspect().template get<serializer_tag>()(t, M(), v, r);
  }
  
};

}}

#endif
