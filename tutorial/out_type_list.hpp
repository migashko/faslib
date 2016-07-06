#ifndef FAS_TUTORIAL_OUT_TYPE_LIST_HPP
#define FAS_TUTORIAL_OUT_TYPE_LIST_HPP

#include <fas/type_list/type_list.hpp>
#include <fas/integral/int_.hpp>
#include <fas/integral/integral_c.hpp>
#include <iostream>

namespace std
{
  ostream& operator << ( ostream& os, fas::empty_list );

  template<int N>
  ostream& operator << ( ostream& os, fas::type_list< fas::int_<N>, fas::empty_list> );

  template<int N, typename R>
  ostream& operator << ( ostream& os, fas::type_list< fas::int_<N>, R > );
  
  template<typename T, T N>
  ostream& operator << ( ostream& os, fas::type_list< fas::integral_c<T, N>, fas::empty_list> );  

  template<typename T, T N, typename R>
  ostream& operator << ( ostream& os, fas::type_list< fas::integral_c<T, N>, R > );
}

namespace std
{

  ostream& operator << ( ostream& os, fas::empty_list )  
  { 
    return os; 
  }

  template<int N>
  ostream& operator << ( ostream& os, fas::type_list< fas::int_<N>, fas::empty_list> )  
  { 
    os << N; 
    return os;
  }

  template<int N, typename R>
  ostream& operator << ( ostream& os, fas::type_list< fas::int_<N>, R > )  
  {
    os << N << ", " << R(); 
    return os;
  }

  template<typename T, T N>
  ostream& operator << ( ostream& os, fas::type_list< fas::integral_c<T, N>, fas::empty_list> )  
  { 
    os << N; 
    return os;
  }

  template<typename T, T N, typename R>
  ostream& operator << ( ostream& os, fas::type_list< fas::integral_c<T, N>, R > )  
  {
    os << N << ", " << R(); 
    return os;
  }

}

#endif
