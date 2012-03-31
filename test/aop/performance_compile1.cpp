#include "performance_compile.hpp"
#include <fas/aop/aspect_class.hpp>

typedef fas::aspect<
  generate_aspect< 
    //type_list_type< _1, _2 > 
    type_list_inherit< _1, _2 > 
  >::type
> aspect_type;

struct aspect: aspect_type {};

/*struct aspect_class:
  fas::aspect_class< aspect_type >
{};
*/

typedef fas::aspect_class< aspect_type > aspect_class;

int main()
{
  typedef type_list_inherit< int_<0>, int_<10> > list;
  enum { 
    value = fas::static_check< fas::length<list>::value == 10 >::value
  };
 
  aspect_class ac;
  
  return ac.get_aspect(). get< _tag_< int_<1> > >()(ac);
}
