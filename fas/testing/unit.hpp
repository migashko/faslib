//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TESTING_UNIT_HPP
#define FAS_TESTING_UNIT_HPP

#include <string>
#include <fas/aop/advice.hpp>
#include <fas/aop/group.hpp>
#include <fas/testing/tags.hpp>

namespace fas{ namespace testing{

class t_unit
{
  std::string _name;
  std::string _desc;

public:
  ~t_unit(){}
  t_unit(const std::string& name = "", const std::string& desc = "")
   : _name(name), _desc(desc)
  {
  }
  const std::string& fas_name() const { return _name; }
  const std::string& fas_desc() const { return _desc; }
};

}}

#define UNIT(name, desc)\
struct fas_##name##_unit: ::fas::testing::t_unit\
{ \
  fas_##name##_unit(): t_unit( #name, desc) { }\
\
  template<typename T>\
  void operator()(T& t) const;\
};\
\
struct fas_##name##_tag;\
struct fas_##name##_type_list: ::fas::type_list< ::fas::advice<fas_##name##_tag, fas_##name##_unit>, ::fas::type_list< ::fas::group< ::fas::testing::_units_, fas_##name##_tag> > > {};\
template<typename T>\
void fas_##name##_unit::operator()(T& t) const

#endif
