#define MAX_ASPECT_COUNT 5
#define MAX_ADVICE_COUNT 50

#include <fas/integral.hpp>
#include <fas/algorithm.hpp>
#include <fas/mp/lambda.hpp>
#include <fas/type_list.hpp>
#include <fas/aop/advice.hpp>
#include <fas/aop/aspect.hpp>

#include <iostream>

using fas::_;
using fas::_1;
using fas::_2;
using fas::int_;
using fas::a;
using fas::p;

template<typename N>
struct _tag_;


template<typename  N>
struct ad_advice
{
  template<typename T>
  int operator()(T& t)
  {
    std::cout << N::value << std::endl;
    return t.get_aspect().template get< _tag_< int_< N::value+1> > >()(t) ;
  }
};


template<>
struct ad_advice< int_< MAX_ADVICE_COUNT - 1 > >
{
  template<typename T>
  int operator()(T& t)
  {
    //t.error();
    std::cout << MAX_ADVICE_COUNT - 1 << " OK" << std::endl;
    return 0;
  }
};


template<typename N>
struct advice: 
  fas::advice< _tag_< int_<N::value> >, ad_advice< int_< N::value > > >
{};

template<typename FROM, typename COUNT>
struct generate_list
{
   typedef typename fas::generate< COUNT, fas::generator< FROM, fas::inc<_> > >::type type_numbers;
   typedef typename fas::transform< type_numbers, advice<_> >::type type;
};

template<typename FROM, typename COUNT>
struct type_list_type
{
  typedef typename generate_list<FROM, COUNT>::type type;
};

template<typename FROM, typename COUNT>
struct type_list_inherit
  : generate_list<FROM, COUNT>::type
{
};

template< 
  typename GG, /* =  type_list_inherit */
  typename TOTAL = int_<MAX_ADVICE_COUNT>, 
  typename COUNT = int_<MAX_ASPECT_COUNT> >
struct generate_aspect
{
  typedef typename fas::generate<
    typename fas::divides<TOTAL,COUNT>::type,
    fas::generator<
      fas::pair< int_<0>, typename fas::apply< GG, int_<0>, COUNT >::type >,
      fas::pair<
        fas::plus< fas::first< _1 >, COUNT >,
        
        //fas::apply< fas::second<_1>, a< fas::first< p<_1> > >, COUNT >
        //type_list_type< fas::first< _1 >, COUNT>
        //typename fas::apply< GG , fas::first< _1 >, COUNT >::binded_types
        typename fas::lambda< GG >::template apply<
          fas::first< _1 >,
          COUNT
        >
        
        //cfas::apply< GG, fas::first< a< p<_1> > >, COUNT >
      >
      /*typename fas::lambda<GG>::template apply< 
        fas::plus< _, COUNT >, 
        COUNT 
      >
      */
    >
  >::type type_list_pair;
  
  typedef typename fas::transform< type_list_pair, fas::second<_> >::type type_list;
  
  typedef fas::aspect< type_list > type;
};

