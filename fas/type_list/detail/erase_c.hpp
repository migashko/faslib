//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2007, 2011, 2012
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TYPE_LIST_DETAIL_ERASE_HPP
#define FAS_TYPE_LIST_DETAIL_ERASE_HPP


#include <fas/type_list/split_c.hpp>
#include <fas/type_list/merge.hpp>

#include <fas/type_list/errorlist.hpp>
#include <fas/type_list/length.hpp>

#include <fas/static_check/static_error.hpp>

namespace fas{ namespace detail{

template<int I, typename L>
struct erase_impl1;


#ifdef FASLIB_TYPE_LIST_CHECK

template<int I,typename L>
struct erase_impl
  : static_error< 
      errorlist::out_of_range< I, length<L>::value >, 
      ( (I>=0) && (I < length<L>::value) )
    >::type
  , erase_impl1< I, L>
{
};

#else

template<int I,typename L>
struct erase_impl
  : erase_impl1< I, L>
{
};

#endif


template<int I, typename L>
struct erase_impl1
{
  typedef typename split_c<I, L>::left_list left_list;
  typedef typename split_c<I, L>::right_list right_list;

  typedef typename merge<
      left_list,
      typename right_list::right_type
  >::type type;
};


}}


#endif
