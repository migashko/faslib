//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#include <fas/type_list.hpp>
#include <fas/algorithm/accumulate.hpp>
#include <fas/typemanip.hpp>
#include <fas/integral.hpp>
#include <fas/static_check.hpp>
#include <fas/mp.hpp>

#include <iostream>
using namespace ::fas;

struct list0: empty_list {};
struct list1: type_list_n< int_<1> >::type {};
struct list2: type_list_n< int_<1>, int_<2> >::type {};

#if __cplusplus >= 201103L

typedef fas::int_<1> O;

constexpr double pi = 
    double( fas::accumulate_t< fas::type_list_n_nocheck< 
    
                        O,O,O,O,O,O,              
                    O,O,O,O,O,O,O,O,O,O,          
                  O,O,O,O,O,O,O,O,O,O,O,O,        
                  O,O,O,O,O,O,O,O,O,O,O,O,        
                O,O,O,O,O,O,O,O,O,O,O,O,O,O,      
                O,O,O,O,O,O,O,O,O,O,O,O,O,O,      
                O,O,O,O,O,O,O,O,O,O,O,O,O,O,      
              O,O,O,O,O,O,O,O,O,O,O,O,O,O,O,O,    
              O,O,O,O,O,O,O,O,O,O,O,O,O,O,O,O,    
              O,O,O,O,O,O,O,O,O,O,O,O,O,O,O,O,
              O,O,O,O,O,O,O,O,O,O,O,O,O,O,O,O,
                O,O,O,O,O,O,O,O,O,O,O,O,O,O,
                O,O,O,O,O,O,O,O,O,O,O,O,O,O,
                O,O,O,O,O,O,O,O,O,O,O,O,O,O,
                  O,O,O,O,O,O,O,O,O,O,O,O,
                  O,O,O,O,O,O,O,O,O,O,O,O,
                    O,O,O,O,O,O,O,O,O,O,
                        O,O,O,O,O,O
                        
    >::type, fas::plus, fas::int_<0> >::type::value ) 
    
                                    //
                                   //
                                  //
                                 //
                                //
                               //
                              /
                             //
                            //
                           //
                          //
                         //
                        //
                        
    double( fas::accumulate_t< fas::type_list_n_nocheck< 
    
                      O,O,O,O,O,O,O,O,
                      O,O,O,O,O,O,O,O,
                      O,O,O,O,O,O,O,O,
                      O,O,O,O,O,O,O,O,
                      O,O,O,O,O,O,O,O,
                      O,O,O,O,O,O,O,O,
                      O,O,O,O,O,O,O,O,
                      O,O,O,O,O,O,O,O,
                      O,O,O,O,O,O,O,O
                      
    >::type, fas::plus, fas::int_<0> >::type::value );


#endif

int main()
{
 
    
  enum 
  {
    value = static_check< accumulate<list0, fas::plus<_1, _2>, fas::int_<21> >::type::value == 21 >::value
          + static_check< accumulate<list1, fas::plus<_1, _2>, fas::int_<1> >::type::value == 2 >::value
          + static_check< accumulate<list2, fas::plus<_1, _2>, fas::int_<0> >::type::value == 3 >::value
          #if __cplusplus >= 201103L
          // pi == 3.16667F
          + static_check< (pi > 3.16666F) && pi < (3.16668F) >::value
          #endif
  };
  
  return 0;
}
