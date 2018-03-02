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

using namespace ::fas;

struct list0: empty_list {};
struct list1: type_list_n< int_<1> >::type {};
struct list2: type_list_n< int_<1>, int_<2> >::type {};

#if __cplusplus >= 201103L /*&& !defined(FASLIB_TYPE_LIST_CHECK)*/
// For FASLIB_TYPE_LIST_CHECK needs -ftemplate-depth=1400 or more 

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
                        
    >::type, fas::int_<0>, fas::plus >::type::value ) 
    
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
                      
    >::type, fas::int_<0>, fas::plus >::type::value );


#endif

struct A; struct B; struct C;
typedef fas::type_list_n< A, B, C >::type list4;
typedef fas::accumulate<list4, empty_list, push_front<_1, _2> >::type res4;
typedef fas::reverse<list4>::type chk4;

int main()
{
  enum 
  {
    value = static_check< accumulate<list0, fas::int_<21>, fas::plus<_1, _2> >::type::value == 21 >::value
          + static_check< accumulate<list1, fas::int_<1>,  fas::plus<_1, _2> >::type::value == 2 >::value
          + static_check< accumulate<list2, fas::int_<0>,  fas::plus<_1, _2> >::type::value == 3 >::value
          #if __cplusplus >= 201103L /*&& !defined(FASLIB_TYPE_LIST_CHECK)*/
          // pi == 3.16667F
          + static_check< (pi > 3.16666F) && pi < (3.16668F) >::value
          #endif
          + static_check< same_type<res4, chk4>::value >::value
  };
  
  return 0;
}
