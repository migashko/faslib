#ifndef FAS_SERIALIZATION_JSON_PARSER_HPP
#define FAS_SERIALIZATION_JSON_PARSER_HPP

#include <fas/aop/aspect_class.hpp>
#include <fas/serialization/parser/aspect.hpp>

namespace fas{ namespace json{

template<typename A = ::fas::aspect<> >
class parser
  : public aspect_class<A, parser::aspect >
{
  typedef aspect_class<A, parser::aspect > super;
public:
  typedef typename super::aspect aspect;
  
  template<typename R>
  R operator()(R r)
  {
    return parse(*this,r);
  }
  
protected:
  
  template<typename T, typename R>
  R parse(T& t, R r)
  {
    r = t.get_aspect().template get<_space_>()(t, r);
    r = t.get_aspect().template get<_value_>()(t, r);
    return r;
  }
  
};

}}

#endif
