//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2007, 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TYPE_LIST_TYPE_LIST_N_HPP
#define FAS_TYPE_LIST_TYPE_LIST_N_HPP

#include <fas/type_list/organize.hpp>
#include <fas/type_list/type_list.hpp>
#include <fas/type_list/empty_list.hpp>


namespace fas{

template< typename T1 = empty_list,  typename T2 = empty_list,  typename T3 = empty_list,  
          typename T4 = empty_list,  typename T5 = empty_list,  typename T6 = empty_list,
          typename T7 = empty_list,  typename T8 = empty_list,  typename T9 = empty_list,  
          typename T10 = empty_list, typename T11 = empty_list, typename T12 = empty_list,
          typename T13 = empty_list, typename T14 = empty_list, typename T15 = empty_list, 
          typename T16 = empty_list, typename T17 = empty_list, typename T18 = empty_list,
          typename T19 = empty_list, typename T20 = empty_list, typename T21 = empty_list, 
          typename T22 = empty_list, typename T23 = empty_list, typename T24 = empty_list,
          typename T25 = empty_list, typename T26 = empty_list
>
struct type_list_n
{

  typedef typename organize<
      type_list< T1,  type_list< T2,  type_list< T3,  type_list< T4,
      type_list< T5,  type_list< T6,  type_list< T7,  type_list< T8,
      type_list< T9,  type_list< T10, type_list< T11, type_list< T12,
      type_list< T13, type_list< T14, type_list< T15, type_list< T16,
      type_list< T17, type_list< T18, type_list< T19, type_list< T20,
      type_list< T21, type_list< T22, type_list< T23, type_list< T24,
      type_list< T25, type_list< T26
      > >
          > > > >
                  > > > > > >
            > >
                  > > > > > >
          > > > >
      > >
  >::type type;

};

}

#endif
