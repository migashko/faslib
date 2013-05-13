//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011, 2012
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TYPEMANIP_SWITCH__HPP
#define FAS_TYPEMANIP_SWITCH__HPP

#include <fas/typemanip/if_c.hpp>
#include <fas/typemanip/empty_type.hpp>


namespace fas{


template<
  typename P0 = empty_type, 
  typename P1 = empty_type, 
  typename P2 = empty_type, 
  typename P3 = empty_type, 
  typename P4 = empty_type
>
struct switch_
{
  typedef if_c< P4::value, typename P4::case_type, empty_type > if4;
  typedef if_c< P3::value, typename P3::case_type, typename if4::type > if3;
  typedef if_c< P2::value, typename P2::case_type, typename if3::type > if2;
  typedef if_c< P1::value, typename P1::case_type, typename if2::type > if1;
  typedef if_c< P0::value, typename P0::case_type, typename if1::type > if0;
  
  typedef typename if0::type type;
  
  enum 
  { 
    value =    if0::value 
            || if1::value
            || if2::value
            || if3::value
            || if4::value 
  };
};

template<
  typename P0,
  typename P1,
  typename P2,
  typename P3
>
struct switch_<P0, P1, P2, P3, empty_type>
{
  typedef if_c< P3::value, typename P3::case_type, empty_type > if3;
  typedef if_c< P2::value, typename P2::case_type, typename if3::type > if2;
  typedef if_c< P1::value, typename P1::case_type, typename if2::type > if1;
  typedef if_c< P0::value, typename P0::case_type, typename if1::type > if0;
  
  typedef typename if0::type type;
  
  enum 
  { 
    value =    if0::value 
            || if1::value
            || if2::value
            || if3::value
  };
};

template<
  typename P0,
  typename P1,
  typename P2
>
struct switch_<P0, P1, P2, empty_type, empty_type>
{  
  typedef if_c< P2::value, typename P2::case_type, empty_type > if2;
  typedef if_c< P1::value, typename P1::case_type, typename if2::type > if1;
  typedef if_c< P0::value, typename P0::case_type, typename if1::type > if0;
  
  typedef typename if0::type type;
  
  enum 
  { 
    value =    if0::value 
            || if1::value
            || if2::value
  };
};

template<
  typename P0,
  typename P1
>
struct switch_<P0, P1, empty_type, empty_type, empty_type>
{  
  typedef if_c< P1::value, typename P1::case_type, empty_type > if1;
  typedef if_c< P0::value, typename P0::case_type, typename if1::type > if0;
  
  typedef typename if0::type type;
  
  enum 
  { 
    value =    if0::value 
            || if1::value
  };
};

template< typename P0 >
struct switch_<P0, empty_type, empty_type, empty_type, empty_type>
  : if_c< P0::value, typename P0::case_type, empty_type >
{  
};

template<>
struct switch_< empty_type, empty_type, empty_type, empty_type, empty_type>
{  
  enum {value =0 };
  typedef empty_type type;
};

}

#endif
