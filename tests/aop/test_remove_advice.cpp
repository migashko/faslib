//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#include <fas/type_list/type_list_n.hpp>
#include <fas/type_list/length.hpp>
#include <fas/type_list/type_at_c.hpp>
#include <fas/aop/remove_advice.hpp>
#include <fas/aop/value_advice.hpp>
#include <fas/aop/aspect.hpp>
#include <fas/aop/aspect_class.hpp>
#include <fas/static_check/static_check.hpp>

struct _tag1_;
struct _tag2_;

struct aspect1: fas::aspect< fas::type_list_n<
  fas::value_advice< _tag1_, int >,
  fas::value_advice< _tag2_, int >
>::type >
{};

struct aspect2: fas::aspect< fas::type_list_n<
  fas::value_advice< _tag1_, long long >,
  fas::remove_advice<_tag1_>,
  aspect1
>::type >
{};




int main()
{
  typedef fas::aspect_class<aspect1> class1;
  typedef fas::aspect_class<aspect2> class2;
  
  
  enum 
  { 
    result = fas::static_check< sizeof(class1)==sizeof(int)*2 >::value
           + fas::static_check< fas::length<typename class2::aspect::common_list>::value == 2 >::value
           + fas::static_check< fas::length<typename class2::aspect::hierarchy_list>::value == 2 >::value
           + fas::static_check<  sizeof( fas::type_at_c< 0, typename class2::aspect::hierarchy_list>::type ) == sizeof(long long) >::value
           + fas::static_check<  sizeof( fas::type_at_c< 1, typename class2::aspect::hierarchy_list>::type ) == sizeof(int) >::value
           + fas::static_check< sizeof(class2)== ( sizeof(int)*2 /*aligment*/ + sizeof(long long) )>::value
  };
  /*
enum 
  { 
      value = static_check< 
                  some_type< 
                    int_<1>, 
                    find_advice<_tag1_, advice_list>::type::advice_class
                  >::value 
                >::value
              +
              static_check< 
                  some_type< 
                    int_<2>, 
                    find_advice<_tag4_, advice_list>::type::advice_class
                  >::value 
                >::value,
  };
  */
  return 0;
}
