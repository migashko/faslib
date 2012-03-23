//
// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_AOP_GROUP_CALL_HPP
#define FAS_AOP_GROUP_CALL_HPP

#include <fas/aop/metalist.hpp>
#include <fas/aop/tag.hpp>
#include <fas/algorithm/select.hpp>
#include <fas/mp/lambda.hpp>

namespace fas {

namespace detail
{
  template<typename T, typename F >
  inline F for_each_group(empty_list, T&, F f) { return f; }

  template<typename L, typename R, typename T, typename F >
  inline F for_each_group(type_list<L, R>, T& t, F f )
  {
    // f( t, tag<L>(), t.get_aspect().template get<L>() );
    //f.operator() template <L>(t);
    
    // f.template operator()<L>(t);
    f(t, tag<L>() );
    return for_each_group( R(), t, f);
  }

  /*
  template<typename L, typename R, typename T, typename F >
  inline F for_each_group(type_list<L, R>, const T& t, F f ) 
  {
    f( t, t.get_aspect().template get<L>() );
    return for_each_group( R(), t, f);
  }*/

  /// 0
  template<typename T >
  inline void group_call_helper(empty_list, T&) { }

  template<typename L, typename R, typename T >
  inline void group_call_helper(type_list<L, R>, T& t )
  {
    t.get_aspect().template get<L>()(t);
    group_call_helper( R(), t);
  }


  /// 1
  template<typename T, typename P1 >
  inline void group_call_helper(empty_list, T&, P1) { }

  template<typename L, typename R, typename T, typename P1 >
  inline void group_call_helper(type_list<L, R>, T& t, P1 p1)
  {
    t.get_aspect().template get<L>()(t, p1);
    group_call_helper( R(), t, p1);
  }

  /// 2
  template<typename T, typename P1, typename P2 >
  inline void group_call_helper(empty_list, T&, P1, P2) { }

  template<typename L, typename R, typename T, typename P1, typename P2 >
  inline void group_call_helper(type_list<L, R>, T& t, P1 p1, P2 p2)
  {
    t.get_aspect().template get<L>()(t, p1, p2);
    group_call_helper( R(), t, p1, p2);
  }

  /// 3
  template<typename T, typename P1, typename P2, typename P3 >
  inline void group_call_helper(empty_list, T&, P1, P2, P3) { }

  template<typename L, typename R, typename T, typename P1, typename P2, typename P3 >
  inline void group_call_helper(type_list<L, R>, T& t, P1 p1, P2 p2, P3 p3)
  {
    t.get_aspect().template get<L>()(t, p1, p2, p3);
    group_call_helper( R(), t, p1, p2, p3);
  }

  /// 4
  template<typename T, typename P1, typename P2, typename P3, typename P4 >
  inline void group_call_helper(empty_list, T&, P1, P2, P3, P4) { }

  template<typename L, typename R, typename T, typename P1, typename P2, typename P3, typename P4 >
  inline void group_call_helper(type_list<L, R>, T& t, P1 p1, P2 p2, P3 p3, P4 p4)
  {
    t.get_aspect().template get<L>()(t, p1, p2, p3, p4);
    group_call_helper( R(), t, p1, p2, p3, p4);
  }

  /// 5
  template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5 >
  inline void group_call_helper(empty_list, T&, P1, P2, P3, P4, P5) { }

  template<typename L, typename R, typename T, typename P1, typename P2, typename P3, typename P4, typename P5 >
  inline void group_call_helper(type_list<L, R>, T& t, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5)
  {
    t.get_aspect().template get<L>()(t, p1, p2, p3, p4, p5);
    group_call_helper( R(), t, p1, p2, p3, p4, p5);
  }
}

template<typename T, template<typename> class IF >
struct aspect_predicate
{
  template<typename Tg>
  struct apply
  {
    typedef typename T::aspect::template advice_cast<Tg>::type advice_type;
    typedef typename IF<advice_type>::type type;
  };
};

template<typename Tg>
class group_call
{
public:
  
  typedef metalist::advice metatype;
  typedef Tg tag;
  typedef group_call<Tg> advice_class;

  advice_class& get_advice() { return *this;}
  const advice_class& get_advice() const { return *this;}

  template<typename T, typename F>
  F for_each(T& t, F f)
  {
    typedef typename T::aspect::template select_group<Tg>::type group_tags;
    return detail::for_each_group( group_tags(), t, f );
  }

  template< template<typename> class IF, typename T, typename F>
  F for_each_if_t(T& t, F f)
  {
    typedef typename T::aspect::template select_group<Tg>::type group_tags;
    //typedef typename aspect_predicate<T, IF>::apply<int>::type
    typedef typename select_t< group_tags, aspect_predicate<T, IF>::template apply >::type selected_tags;
    return detail::for_each_group( selected_tags(), t, f );
  }
  
  template< class IF, typename T, typename F>
  F for_each_if(T& t, F f)
  {
    return for_each_if_t< lambda< FAS_T_SIMPLIFY(IF) >::template apply >(t, f);
    /*typedef typename T::aspect::template select_group<Tg>::type group_tags;
    //typedef typename aspect_predicate<T, IF>::apply<int>::type
    typedef typename select_t< group_tags, aspect_predicate<T, IF>::template apply >::type selected_tags;
    return detail::for_each_group( selected_tags(), t, f );
    typedef typename detail::select_helper_t<L, lambda< FAS_T_SIMPLIFY(F) >::template apply >::type type;
    */
  }

  
  /*
  template<typename T, typename F>
  F for_each(const T& t, F f)
  {
    typedef typename T::aspects::template select_group<Tg>::type group_tags;
    return detail::for_each_group( group_tags(), t, f );
  }
  */

  template<typename T>
  void operator()(T& t)
  {
    typedef typename T::aspect::template select_group<Tg>::type group_tags;
    detail::group_call_helper( group_tags(), t);
  }

  template<typename T, typename P1>
  void operator()(T& t, P1 p1)
  {
    typedef typename T::aspect::template select_group<Tg>::type group_tags;
    detail::group_call_helper( group_tags(), t, p1);
  }

  template<typename T, typename P1, typename P2>
  void operator()(T& t, P1 p1, P2 p2)
  {
    typedef typename T::aspect::template select_group<Tg>::type group_tags;
    detail::group_call_helper( group_tags(), t, p1, p2);
  }

  template<typename T, typename P1, typename P2, typename P3>
  void operator()(T& t, P1 p1, P2 p2, P3 p3) 
  {
    typedef typename T::aspect::template select_group<Tg>::type group_tags;
    detail::group_call_helper( group_tags(), t, p1, p2, p3);
  }

  template<typename T, typename P1, typename P2, typename P3, typename P4>
  void operator()(T& t, P1 p1, P2 p2, P3 p3, P4 p4) 
  {
    typedef typename T::aspect::template select_group<Tg>::type group_tags;
    detail::group_call_helper( group_tags(), t, p1, p2, p3, p4);
  }

  template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5>
  void operator()(T& t, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5)
  {
    typedef typename T::aspect::template select_group<Tg>::type group_tags;
    detail::group_call_helper( group_tags(), t, p1, p2, p3, p4, p5);
  }

private:
  /*
  // TODO: вынести в хелпер как inline функции
  template<typename L, typename R, typename T >
  void _call(type_list<L, R>, T& t ) 
  {
    t.get_aspect().template get<L>()(t);
    _call( R(), t);
  }

  template<typename T >
  void _call(empty_list, T&) { }

  // 1
  template<typename L, typename R, typename T, typename P1 >
  void _call(type_list<L, R>, T& t, P1 p1)
  {
    t.get_aspect().template get<L>()(t, p1);
    _call( R(), t, p1);
  }

  template<typename T, typename P1 >
  void _call(empty_list, T&, P1) { }
  */

};


}

#endif
