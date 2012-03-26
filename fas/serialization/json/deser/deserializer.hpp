#ifndef FAS_SERIALIZATION_JSON_DESER_DESERIALIZER_HPP
#define FAS_SERIALIZATION_JSON_DESER_DESERIALIZER_HPP

/*
#include <fas/aop/aspect_class.hpp>
#include <fas/serialization/json/deser/aspect.hpp>
#include <fas/serialization/json/parser/aspect.hpp>

namespace fas{ namespace json{ namespace deser{

template<typename A = ::fas::aspect<> >
class deserializer
  : public aspect_class< A, 
              typename aspect_merge< 
                aspect, 
                ::fas::json::parse::aspect
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

}}}
*/

#endif
