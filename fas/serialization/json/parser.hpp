#ifndef FAS_SERIALIZATION_JSON_PARSER_HPP
#define FAS_SERIALIZATION_JSON_PARSER_HPP

#include <fas/aop/aspect_class.hpp>
#include <fas/serialization/json/parser/aspect.hpp>
#include <utility>

namespace fas{ namespace json{

template<typename A = ::fas::aspect<> >
class parser
  : public aspect_class<A, parse::aspect >
{
  typedef aspect_class<A, parse::aspect > super;
public:
  typedef typename super::aspect aspect;

  operator bool () const
  {
    return !super::get_aspect().template get<_except_>();
  }
  
  template<typename R>
  R operator()(R r)
  {
    return parse(*this,r);
  }
  
  template<typename R, typename RD>
  std::pair<R, RD> operator()(R r, RD rd)
  {
    return copy(*this,r, rd);
  }

  template<typename R>
  R parse(R r)
  {
    return parse(*this,r);
  }

  template<typename R, typename RD>
  std::pair<R, RD> copy(R r, RD rd)
  {
    return copy(*this,r, rd);
  }

  template<typename R>
  bool is_null(R r) {  return super::get_aspect().template get< parse::_null_>().check(r); }

  template<typename R>
  bool is_bool(R r) {  return super::get_aspect().template get< parse::_boolean_>().check(r); }

  template<typename R>
  bool is_number(R r) {  return super::get_aspect().template get< parse::_number_>().check(r); }

  template<typename R>
  bool is_string(R r) {  return super::get_aspect().template get< parse::_string_>().check(r); }

  template<typename R>
  bool is_array(R r) {  return super::get_aspect().template get< parse::_array_>().check(r); }

  template<typename R>
  bool is_object(R r) {  return super::get_aspect().template get< parse::_object_>().check(r); }

/// /// 
  template<typename R>
  R parse_null(R r) {  return super::get_aspect().template get< parse::_null_>()(*this, r); }

  template<typename R>
  R parse_bool(R r) {  return super::get_aspect().template get< parse::_boolean_>()(*this, r); }

  template<typename R>
  R parse_number(R r) {  return super::get_aspect().template get< parse::_number_>()(*this, r); }

  template<typename R>
  R parse_string(R r) {  return super::get_aspect().template get< parse::_string_>()(*this, r); }

  template<typename R>
  R parse_value(R r) {  return super::get_aspect().template get< parse::_value_>()(*this, r); }

  template<typename R>
  R parse_array(R r) {  return super::get_aspect().template get< parse::_array_>()(*this, r); }

  template<typename R>
  R parse_object(R r) {  return super::get_aspect().template get< parse::_object_>()(*this, r); }

  template<typename R>
  R parse_space(R r) {  return super::get_aspect().template get< parse::_space_>()(*this, r); }
  
  template<typename T, typename R>
  R parse(T& t, R r)
  {
    r = t.get_aspect().template get< parse::_space_>()(t, r);
    r = t.get_aspect().template get< parse::_value_>()(t, r);
    return r;
  }

  template<typename T, typename R, typename RD>
  std::pair<R, RD> copy(T& t, R r, RD rd)
  {
    r = t.get_aspect().template get< parse::_space_>()(t, r);
    return t.get_aspect().template get< parse::_value_>()(t, r, rd);
  }

};

}}

#endif
