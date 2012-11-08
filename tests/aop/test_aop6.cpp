//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#include <fas/type_list/type_list_n.hpp>
#include <fas/type_list/length.hpp>
#include <fas/type_list/type_at_c.hpp>
#include <fas/aop/remover.hpp>
#include <fas/aop/value_advice.hpp>
#include <fas/aop/aspect.hpp>
#include <fas/aop/stub.hpp>
#include <fas/aop/aspect_class.hpp>
#include <fas/static_check/static_check.hpp>

struct _tag1_;
struct _tag2_;
struct _tag3_;
struct _tag4_;
struct _tag5_;
struct _tag6_;



struct aspect1: fas::aspect< fas::type_list_n<
  fas::stub<_tag1_>,
  fas::stub<_tag2_>,
  fas::stub<_tag3_>,
  fas::stub<_tag4_>,
  fas::stub<_tag5_>,
  fas::stub<_tag6_>
>::type >
{};

struct aspect2: fas::aspect< fas::type_list_n<
  fas::value_advice< _tag4_, int >,
  fas::type_advice< _tag5_, int >,
  fas::stub<_tag6_>
>::type >
{};

struct aspect3: fas::aspect< fas::type_list_n<
  fas::remover<_tag1_>,
  fas::remover<_tag3_>,
  fas::remover<_tag5_>,
  aspect1,
  aspect2
>::type >
{};


int main()
{
  typedef fas::aspect_class<aspect3> class3;
  
  enum 
  { 
    result = fas::static_check< class3::aspect::has_advice<_tag1_>::value == 0 >::value
           + fas::static_check< class3::aspect::has_advice<_tag2_>::value == 1 >::value
           + fas::static_check< class3::aspect::has_advice<_tag3_>::value == 0 >::value
           + fas::static_check< class3::aspect::has_advice<_tag4_>::value == 1 >::value
           + fas::static_check< class3::aspect::has_advice<_tag5_>::value == 0 >::value
           + fas::static_check< class3::aspect::has_advice<_tag6_>::value == 1 >::value
  };
  
  return 0;
}
