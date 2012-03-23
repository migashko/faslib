// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_AOP_ASPECT_HIERARCHY_HPP
#define FAS_AOP_ASPECT_HIERARCHY_HPP

#include <fas/aop/metalist.hpp>
#include <fas/aop/make_advice_list.hpp>
#include <fas/aop/find_advice.hpp>
#include <fas/aop/is_advice.hpp>
#include <fas/aop/is_alias.hpp>
#include <fas/aop/is_group.hpp>
#include <fas/aop/aspect_select.hpp>
#include <fas/aop/aspect_select_t.hpp>
#include <fas/aop/aspect_select_group.hpp>
#include <fas/aop/group_call.hpp>
#include <fas/hierarchy/scatter_hierarchy.hpp>
#include <fas/hierarchy/field.hpp>
#include <fas/algorithm/any.hpp>
#include <fas/algorithm/transform.hpp>
#include <fas/algorithm/transform_tail_if.hpp>
#include <fas/algorithm/erase_if.hpp>
#include <fas/integral/or_.hpp>

#include <fas/typemanip/if_c.hpp>
#include <fas/type_list/type_list.hpp>
#include <fas/type_list/empty_list.hpp>
namespace fas{
  
template<typename T>
struct is_advice_or_alias
{
  enum { value = is_advice<T>::value || is_alias<T>::value };
  typedef bool_<value> type;
};


template<typename Tg>
struct not_has_tag
{
  template<typename T>
  struct apply{
    enum { value = !is_has_tag< T, Tg >::value };
    typedef bool_<value> type;
  };
};

template<typename L>
struct remove_advices;

// TODO: no type_list spec
// TODO: transform_tail_if_t
template<typename L, typename R>
struct remove_advices< type_list<L, R> >
{
  typedef typename if_c<
    is_del<L>::value,
    typename remove_advices< 
      typename erase_if_t< R, bind2nd< is_has_tag, typename get_tag<L>::type  >::template apply >::type
    >::type,
    type_list<L, typename remove_advices<R>::type >
  >::type type;
  
};

template<>
struct remove_advices< empty_list >
{
  typedef empty_list type;
};

template< template<typename> class F >
struct metafunc
{
  template<typename T>
  struct apply
  {
    typedef F<T> type;
  };
};

template<typename A>
struct aspect_traits
{
  typedef A aspect_type;
//1  typedef typename aspect_select_t<aspect_type, is_advice>::type advice_list;
//2  typedef typename aspect_select_t<aspect_type, lambda_r< or_< is_advice<_1>, is_del<_1> >, 1 >::template apply >::type advice_list1;
//2  typedef typename remove_advices<advice_list1>::type advice_list2;
//2  typedef typename organize<advice_list2>::type advice_list;
  
  // typedef typename aspect_select_t<aspect_type, lambda_r< or_< is_advice<_1>, is_del<_1> >, 1 >::template apply >::type advice_list1;
  typedef typename aspect_select<aspect_type, or_< is_advice<_1>, is_del<_1> > >::type advice_list1;
  typedef typename transform_tail_if<
    advice_list1,
    erase_if<
      tail< _1 >,
      a< is_has_tag< p<_>, get_tag< head< _1 > > > >
    >,
    is_del<_>
  >::type advice_list;
  
  typedef typename aspect_select_t<aspect_type, is_group>::type group_list;
  //typedef typename aspect_select_t<A, is_advice_or_alias>::type common_list1;
  // typedef typename aspect_select_t<aspect_type, lambda_r< or_< is_advice<_1>, is_alias<_1> >, 1 >::template apply >::type common_list1;
  typedef typename aspect_select<aspect_type, or_< is_advice<_1>, is_alias<_1> > >::type common_list1;
  typedef typename unique<typename transform_t<group_list, get_tag >::type >::type group_tags;
  //!!! typedef typename transform_t<group_tags, lambda_r<group_call<_>, 1>::template apply >::type group_calls;
  //typedef typename transform_t<group_tags, metafunc<group_call>::apply >::type group_calls;
  typedef typename transform<group_tags, group_call<_> >::type group_calls;
  typedef typename merge<group_calls, common_list1>::type common_list2;
  typedef typename unique<common_list2>::type common_list;
  typedef typename merge<group_calls, advice_list>::type hierarchy_list2;
  typedef typename unique<hierarchy_list2>::type hierarchy_list;
};



template<typename A>
class aspect_hierarchy
  : public scatter_hierarchy< typename aspect_traits<A>::hierarchy_list >
{
public:
  //typedef A aspect;
  typedef aspect_traits<A> traits;
  typedef typename traits::hierarchy_list hierarchy_list;
  typedef typename traits::common_list advice_list;
  typedef typename traits::group_list group_list;
  typedef scatter_hierarchy< hierarchy_list > super;
  /*
  //typedef typename make_advice_list<aspect>::type advice_list;
  typedef typename aspect_select_t<aspect, is_advice>::type advice_list;
  typedef scatter_hierarchy< advice_list > super;
  //typedef typename aspect_select<A, true_>::type common_list;
  //typedef typename aspect_select_t<A, any_entity>::type common_list;
  //typedef typename aspect_select<A, empty_type>::type common_list;
  typedef typename aspect_select_t<A, is_advice_or_alias>::type common_list;
  typedef typename aspect_select_t<aspect, is_group>::type group_list;
  typedef typename unique<typename transform<group_list, has_tag<_1> >::type >::type group_tags;
  typedef typename transform<group_tags, group_call<_1> >::type group_calls;
  */


  template<typename Tg>
  typename find_advice< Tg, advice_list>::type::advice_class&
  get()
  {
    typedef typename find_advice< Tg, advice_list>::type advice_type;
    return field<advice_type>( static_cast<super&>(*this) ).get_advice();
  };

  template<typename Tg>
  const typename find_advice< Tg, advice_list>::type::advice_class&
  get() const
  {
    typedef typename find_advice< Tg, advice_list>::type advice_type;
    return const_field<advice_type>( static_cast<const super&>(*this) ).get_advice();
  };

  template<typename Tg>
  struct advice_cast
  {
    typedef typename find_advice< Tg, advice_list>::type::advice_class type;
  };
  
  template<typename Tg>
  struct has_advice
  {
    typedef index_of_if_t< advice_list, bind2nd<is_has_tag, Tg>::template apply > helper;
    
    enum { value = helper::value!=-1 };
  };
  
  // TODO: впихать в аспект и использовать простой get! (или не надо?)
  
  /*template<typename Tg>
  group_call<Tg> getg()
  {
    return group_call<Tg>();
  }*/

  template<typename Tg>
  group_call<Tg> getg() const
  {
    return group_call<Tg>();
  }

  template<typename Tg>
  struct select_group
  {
    typedef typename aspect_select_group<group_list, Tg>::type type;
  };
};

}

#endif
