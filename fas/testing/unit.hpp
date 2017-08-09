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
#include <fas/testing/unit_counts.hpp>

namespace fas{ namespace testing{

class fas_unit
{
  std::string _name;
  std::string _desc;
  unit_counts _counts;

public:
  fas_unit(const std::string& name = "", const std::string& desc = "")
   : _name(name), _desc(desc), _counts()
  {
  }

  const std::string& fas_name() const { return _name; }
  const std::string& fas_desc() const { return _desc; }

  const unit_counts& fas_counts() const { return _counts; }
  unit_counts& fas_counts() { return _counts; }

  bool fas_ready() const { return 0 == (_counts.errors + _counts.fails + _counts.fatals); }
};

}}

#define UNIT(name, desc)\
struct fas_##name##_unit: ::fas::testing::fas_unit\
{ \
  fas_##name##_unit(): fas_unit( #name, desc) { }\
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
