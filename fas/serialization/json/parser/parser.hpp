#ifndef FAS_SERIALIZATION_JSON_PARSER_PARSER_HPP
#define FAS_SERIALIZATION_JSON_PARSER_PARSER_HPP

#include <fas/serialization/json/parser/tags.hpp>
#include <fas/serialization/json/parser/aspect.hpp>

#include <fas/aop/aspect.hpp>
#include <fas/aop/aspect_class.hpp>


namespace fas{ namespace json{ namespace parser{

template<typename A = ::fas::aspect<> >
class parser
  : public ::fas::aspect_class<A, ::fas::json::parser::aspect >
{
  typedef ::fas::aspect_class<A, ::fas::json::parser::aspect > super;
public:
  template<typename R>
  bool is_null(R r) {  return super::get_aspect().template get<_null_>().check(r); }

  template<typename R>
  bool is_bool(R r) {  return super::get_aspect().template get<_boolean_>().check(r); }

  template<typename R>
  bool is_number(R r) {  return super::get_aspect().template get<_number_>().check(r); }

  template<typename R>
  bool is_string(R r) {  return super::get_aspect().template get<_string_>().check(r); }

  template<typename R>
  bool is_array(R r) {  return super::get_aspect().template get<_array_>().check(r); }

  template<typename R>
  bool is_object(R r) {  return super::get_aspect().template get<_object_>().check(r); }

  template<typename R>
  R parse_null(R r) {  return super::get_aspect().template get<_null_>()(*this, r); }

  template<typename R>
  R parse_bool(R r) {  return super::get_aspect().template get<_boolean_>()(*this, r); }

  template<typename R>
  R parse_number(R r) {  return super::get_aspect().template get<_number_>()(*this, r); }

  template<typename R>
  R parse_string(R r) {  return super::get_aspect().template get<_string_>()(*this, r); }

  template<typename R>
  R parse_value(R r) {  return super::get_aspect().template get<_value_>()(*this, r); }

  template<typename R>
  R parse_array(R r) {  return super::get_aspect().template get<_array_>()(*this, r); }

  template<typename R>
  R parse_attr(R r) {  return super::get_aspect().template get<_attr_>()(*this, r); }

  template<typename R>
  R parse_object(R r) {  return super::get_aspect().template get<_object_>()(*this, r); }

  template<typename R>
  R parse_space(R r) {  return super::get_aspect().template get<_space_>()(*this, r); }

  template<typename R>
  R parse(R r)
  {
    r = super::get_aspect().template get<_space_>()(*this, r);
    r = super::get_aspect().template get<_value_>()(*this, r);
    return r;
  }

  template<typename R>
  R operator()(R r)
  {
    return parse(r);
  }

};

}}}

#endif
