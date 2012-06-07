//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#include <fas/aop/advice.hpp>
#include <fas/aop/alias.hpp>
#include <fas/aop/aspect.hpp>
#include <fas/aop/has_tag.hpp>
#include <fas/aop/private/aspect_select.hpp>
#include <fas/aop/private/find_advice.hpp>
#include <fas/type_list/length.hpp>
#include <fas/integral/int_.hpp>
#include <fas/static_check/static_check.hpp>
#include <fas/algorithm/find_if.hpp>
#include <fas/typemanip/type2type.hpp>

using namespace fas
;


struct _tag1_;
struct _tag2_;
struct _tag3_;
struct _tag4_;

struct advice_list:
    type_list_n<
      alias< _tag4_, _tag3_ >,
      alias< _tag3_, _tag2_ >,
      advice< _tag1_, int_<1> >,
      advice< _tag2_, int_<2> >
    >::type
{};


  typedef find_advice<
                      _tag1_, 
                      advice_list 
                    >::type aaa;

int main()
{
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

  return 0;
}
