//
// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TYPE_LIST_DETAIL_UNIQUE_HPP
#define FAS_TYPE_LIST_DETAIL_UNIQUE_HPP

#include <fas/type_list/metalist.hpp>
#include <fas/type_list/type_at_c.hpp>
#include <fas/type_list/type_count.hpp>
#include <fas/type_list/split_c.hpp>

namespace fas{ namespace detail{

template<typename LL, int P, typename L>
struct unique_impl0;

template<typename MT, int P, typename L>
struct unique_impl1;

template<int P, typename L, int>
struct unique_impl2;

template<int P,typename LL, typename RL>
struct unique_impl3;


#ifdef FASLIB_TYPE_LIST_CHECK

template<typename L>
struct unique_verifying;

template<typename L>
struct unique_helper
  : verifying< unique_verifying<L>, check_list<L> >::type
{
};

template<typename L>
struct unique_verifying
  : unique_impl0<L, 0, L>
{
};

#else

template<typename L>
struct unique_helper
  : unique_impl0<L, 0, L>
{
};

#endif

template<typename LL, int P, typename L>
struct unique_impl0
  : unique_impl1<typename LL::metatype, P, L>
{
};

#ifndef DISABLE_TYPE_LIST_SPEC

template<typename LL, typename RR, int P, typename L>
struct unique_impl0<type_list<LL, RR>, P, L >
{
  typedef typename type_at_c< P, L>::type current;
  typedef typename unique_impl2< P, L, (type_count<current, L>::value > 1) >::type type;
};

/*
template<typename LL, typename RR, int P, typename L>
struct unique_impl0<tl<LL, RR>, P, L >
{
  typedef typename type_at_c< P, L>::type current;
  typedef typename unique_impl2< P, L, (type_count<current, L>::value > 1) >::type type;
};
*/

template< int P, typename L>
struct unique_impl0<empty_list, P, L>
{
  typedef L type;
};

/*
template< int P, typename L>
struct unique_impl0<el, P, L>
{
  typedef L type;
};
*/

#endif // DISABLE_TYPE_LIST_SPEC

template<int P, typename L>
struct unique_impl1<metalist::type_list, P, L>
{
  typedef typename type_at_c< P, L>::type current;
  typedef typename unique_impl2< P, L, (type_count<current, L>::value > 1) >::type type;
};

template<int P, typename L>
struct unique_impl1<metalist::empty_list, P, L>
{
  typedef L type;
};

template<int P,typename L, int>
struct unique_impl2
{
  typedef split_c<P, L> splitter;
  typedef typename splitter::left_list left_list;
  typedef typename splitter::right_list right_list;
  
  typedef typename unique_impl3<P, left_list, right_list>::type type;
  /*
  typedef typename right_list::right_type tail;
  typedef typename merge<left_list, tail>::type result_list;
  typedef typename unique_impl0<tail, P, result_list>::type type;
  */
};

template<int P,typename L>
struct unique_impl2<P, L, false>
{
  typedef typename type_at_c< P, L>::tail tail;
  typedef typename unique_impl0<tail, P + 1, L>::type type;
};

template<int P,typename LL, typename RL>
struct unique_impl3
{
  typedef typename RL::right_type tail;
  typedef typename merge<LL, tail>::type result_list;
  typedef typename unique_impl0<tail, P, result_list>::type type;
};

#ifndef DISABLE_TYPE_LIST_SPEC

template<int P,typename LL, typename L, typename R>
struct unique_impl3<P, LL, type_list<L, R> >
{
  typedef typename unique_impl0<
    R, P, 
    typename merge<LL, R>::type
    >::type type;
};

/*
template<int P,typename LL, typename L, typename R>
struct unique_impl3<P, LL, tl<L, R> >
{
  typedef typename unique_impl0<
    R, P, 
    typename merge<LL, R>::type
    >::type type;
};
*/

#endif // DISABLE_TYPE_LIST_SPEC

}}


#endif
