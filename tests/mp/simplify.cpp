//#include <fas/utility.hpp>

#include <fas/integral/make_integral.hpp>
#include <fas/static_check.hpp>
#include <fas/integral/arithmetic.hpp>
#include <fas/typemanip.hpp>
#include <fas/integral/comparisons.hpp>
#include <fas/mp/simplify.hpp>
#include <vector>

using namespace ::fas;



int main()
{
  // enum { x = 2 > 3 ? 3 : 2 };
 
  enum  { value = static_check< 
                    some_type<
                      simplify< 
                        make_bool< less<int_<1>, int_<2> > > 
                      >::type,
                      bool_<true>
                    >::value
                  >::value  
                  +
                  static_check< 
                    some_type<
                      simplify< 
                        make_bool< less<int_<1>, int_<1> > > 
                      >::type,
                      bool_<false>
                    >::value
                  >::value  
                  +
                  static_check< 
                    some_type<
                      simplify< 
                        make_bool< 
                          less<
                            int_<1>, 
                            make_int< plus<int_<1>, int_<1> > >
                          >
                        > 
                      >::type,
                      bool_<true>
                    >::value
                  >::value  
                  +
                  static_check< 
                    some_type<
                      simplify< 
                        make_bool< 
                          less<
                            _1, 
                            make_int< plus<int_<1>, int_<1> > >
                          >
                        > 
                      >::type,
                      make_bool< less<_1, int_<2> > >
                    >::value
                  >::value  
                  
  };
  
  return 0;
}


