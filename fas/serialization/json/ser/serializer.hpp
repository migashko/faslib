#ifndef FAS_SERIALIZATION_JSON_SER_SERIALIZER_HPP
#define FAS_SERIALIZATION_JSON_SER_SERIALIZER_HPP

#include <fas/aop/aspect_class.hpp>
#include <fas/serialization/json/ser/aspect.hpp>
#include <fas/serialization/json/parser/aspect.hpp>

namespace fas{ namespace json{ namespace ser{

  /*
   * template<typename A = ::fas::aspect<> >
class deserializer
  : public aspect_class< A, 
              typename aspect_merge< 
                aspect, 
                ::fas::json::parser::aspect
              >::type 
           >
{
public:
  template<typename M, typename V, typename R>
  R operator()(M, V& v, R r)
  {
    typedef typename M::deserializer_tag deserializer_tag; 
    return this->get_aspect().template get<deserializer_tag>()(*this, M(), v, r);
  }
};


   */
  
template<typename A = ::fas::aspect<> >
class serializer
  : public ::fas::aspect_class<A, typename aspect_merge<  aspect,  ::fas::json::parser::aspect     >::type >
{
public:
  template<typename M, typename V, typename R>
  R operator()(M m, const V& v, R r)
  {
    typedef typename M::serializer_tag serializer_tag; 
    return this->get_aspect().template get<serializer_tag>()(*this, m, v, r);
  }
};

}}}

#endif
