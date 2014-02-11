//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#include <fas/integral.hpp>
#include <fas/static_check.hpp>
#include <fas/typemanip.hpp>
#include <fas/mp/simplify.hpp>
#include <vector>

using namespace ::fas;

int main()
{
  enum  { value = static_check< 
                    same_type<
                      simplify< 
                        make_bool< less<int_<1>, int_<2> > > 
                      >::type,
                      bool_<true>
                    >::value
                  >::value  
                  +
                  static_check< 
                    same_type<
                      simplify< 
                        make_bool< less<int_<1>, int_<1> > > 
                      >::type,
                      bool_<false>
                    >::value
                  >::value  
                  +
                  static_check< 
                    same_type<
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
                    same_type<
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


