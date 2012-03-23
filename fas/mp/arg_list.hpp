// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_MP_ARG_LIST_HPP
#define FAS_MP_ARG_LIST_HPP

#include <fas/type_list/el.hpp>
#include <fas/type_list/tl_n.hpp>
#include <fas/mp/w.hpp>


namespace fas{

template< class F >
struct arg_list { typedef el type; };

template< template<typename> class F, typename P0>
struct arg_list< F<P0> > 
{
  typedef typename tl_n<
      w<P0>
  >::type type;
};

template< template<typename, typename> class F, typename P0, typename P1>
struct arg_list< F<P0, P1> > 
{
  typedef typename tl_n<
      w<P0>,
      w<P1>
  >::type type;
};

template< template<typename, typename, typename> class F, typename P0, typename P1, typename P2 >
struct arg_list< F<P0, P1, P2> > 
{
  typedef typename tl_n<
      w<P0>,
      w<P1>,
      w<P2>
  >::type type;
};

template< template<typename, typename, typename, typename> class F, typename P0, typename P1, typename P2, typename P3 >
struct arg_list< F<P0, P1, P2, P3> > 
{
  typedef typename tl_n<
      w<P0>,
      w<P1>,
      w<P2>,
      w<P3>
  >::type type;
};


template< template<typename, typename, typename, typename, typename> class F, typename P0, typename P1, typename P2, typename P3, typename P4  >
struct arg_list< F<P0, P1, P2, P3, P4> > 
{
  typedef typename tl_n<
      w<P0>,
      w<P1>,
      w<P2>,
      w<P3>,
      w<P4>
  >::type type;
};

}

#endif
