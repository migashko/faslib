#ifndef FAS_ADV_AD_ASPECT_SELECT_HPP
#define FAS_ADV_AD_ASPECT_SELECT_HPP

#include <fas/type_list/type_list_n.hpp>

#include <fas/integral/int_.hpp>
#include <fas/typemanip/if_c.hpp>
#include <fas/typemanip/switch_.hpp>
#include <fas/typemanip/case_c.hpp>
#include <fas/typemanip/default_.hpp>
#include <fas/typemanip/pair.hpp>


namespace fas{

namespace detail
{
  template<typename Tg, typename T>
  struct aspect_select_impl
  {
    typedef typename T::aspect::template advice_cast<Tg>::type type;
  };

  template<typename Tg, typename T1, typename T2 , typename T3 >
  struct aspect_select_helper
  {
    typedef typename switch_<
      typename type_list_n<
        case_c< T1::aspect::template has_advice<Tg>::value, pair< T1, int_<1> > >,
        case_c< T2::aspect::template has_advice<Tg>::value, pair< T2, int_<2> > >,
        case_c< T3::aspect::template has_advice<Tg>::value, pair< T3, int_<3> > >,
        default_< pair< T3, int_<3> > >
      >::type
    >::type selected;
    
    enum { value = second<selected>::type::value };
    typedef typename first<selected>::type type;
    typedef typename aspect_select_impl<Tg, type >::type advice_type;
  };

  template<typename Tg, typename T1, typename T2>
  struct aspect_select_helper< Tg, T1, T2, empty_type>
  {
    typedef typename if_c<
      T1::aspect::template has_advice<Tg>::value,
      pair< T1, int_<1> >, 
      pair< T2, int_<2> >
    >::type selected;
    enum { value = second<selected>::type::value };
    typedef typename first<selected>::type type;
    typedef typename aspect_select_impl<Tg, type >::type advice_type;
  };

  template<typename Tg, typename T1>
  struct aspect_select_helper< Tg, T1, empty_type, empty_type>
  {
    typedef T1 type;
    typedef typename aspect_select_impl<Tg, type >::type advice_type;
    enum { value = 1 };
  };

  /*
  template<typename Tg, typename T1, typename T2 , typename T3 >
  struct aspect_select_helper;

  template<typename Tg, typename T1, typename T2 , typename T3, bool >
  struct aspect_select_impl;

///1
  template<typename Tg, typename T1>
  struct aspect_select_helper<Tg, T1, empty_type, empty_type>
  {
    typedef typename T1::aspect::template advice_cast<Tg>::type type;
  };

///2
  template<typename Tg, typename T1, typename T2>
  struct aspect_select_helper<Tg, T1, T2, empty_type>
  {
    typedef typename aspect_select_impl<Tg, T1, T2, empty_type, T1::aspect::has_advice<Tg>::value >::type
  };
  
  template<typename Tg, typename T1, typename T2, typename T3>
  struct aspect_select_impl<Tg, T1, T2, T3, true>
  {
    typedef typename T1::aspect::template advice_cast<Tg>::type type;
  };

  template<typename Tg, typename T1, typename T2>
  struct aspect_select_impl<Tg, T1, T2, empty_type, false>
  {
    typedef typename T2::aspect::template advice_cast<Tg>::type type;
  };

///3

  template<typename Tg, typename T1, typename T2, typename T3>
  struct aspect_select_helper
  {
    typedef typename aspect_select_impl<Tg, T1, T2, T3, T1::aspect::has_advice<Tg>::value >::type
  };
  
  template<typename Tg, typename T1, typename T2, typename T3>
  struct aspect_select_impl<Tg, T1, T2, T3, false>
  {
    typedef typename aspect_select_impl<Tg, empty_type, T2, T3, T2::aspect::has_advice<Tg>::value >::type
  };

  template<typename Tg, typename T2, typename T3>
  struct aspect_select_impl<Tg, empty_type, T2, T3, true>
  {
    typedef typename T2::aspect::template advice_cast<Tg>::type type;
  };

  template<typename Tg, typename T2, typename T3>
  struct aspect_select_impl<Tg, empty_type, T2, T3, false>
  {
    typedef typename T3::aspect::template advice_cast<Tg>::type type;
  };
  */

}
  
template<typename Tg>
struct switch_by_tag_t
{
  template<typename T1, typename T2 = empty_type, typename T3 = empty_type >
  struct select_t
    : detail::aspect_select_helper<Tg, T1, T2, T3>
  {
  };
  
  template<typename T>
  typename select_t<T>::type& operator()(T& t) { return t; }

  template<typename T1, typename T2>
  typename select_t<T1, T2>::type& operator()(T1& t1, T2& t2) 
  {
    return _(t1, t2, int_<select_t<T1, T2>::value>() ); 
  }

  template<typename T1, typename T2, typename T3>
  typename select_t<T1, T2, T3>::type& operator()(T1& t1, T2& t2, T3& t3) 
  {
    return _(t1, t2, t3, int_<select_t<T1, T2, T3>::value>() ); 
  }

  template<typename T>
  typename select_t<T>::advice_type& advice(T& t) { return t.get_aspect().template get<Tg>(); }

  template<typename T1, typename T2>
  typename select_t<T1, T2>::advice_type& advice(T1& t1, T2& t2) 
  {
    return _advice(t1, t2, int_<select_t<T1, T2>::value>() ); 
  }

  template<typename T1, typename T2, typename T3>
  typename select_t<T1, T2, T3>::advice_type& advice(T1& t1, T2& t2, T3& t3) 
  {
    return _advice(t1, t2, t3, int_<select_t<T1, T2, T3>::value>() ); 
  }

private:

  template<typename T1, typename T2>
  typename select_t<T1, T2>::type& _(T1& t1, T2&, int_<1> ) 
  {
    return t1;
  }

  template<typename T1, typename T2>
  typename select_t<T1, T2>::type& _(T1&, T2& t2, int_<2> ) 
  {
    return t2;
  }

  template<typename T1, typename T2, typename T3>
  typename select_t<T1, T2, T3>::type& _(T1& t1, T2& , T3&, int_<1> ) 
  {
    return t1;
  }

  template<typename T1, typename T2, typename T3>
  typename select_t<T1, T2, T3>::type& _(T1&, T2& t2, T3&, int_<2> ) 
  {
    return t2;
  }

  template<typename T1, typename T2, typename T3>
  typename select_t<T1, T2, T3>::type& _(T1&, T2&, T3& t3, int_<3> ) 
  {
    return t3;
  }

/// 
  template<typename T1, typename T2>
  typename select_t<T1, T2>::advice_type& _advice(T1& t1, T2&, int_<1> ) 
  {
    return t1.get_aspect().template get<Tg>();
  }

  template<typename T1, typename T2>
  typename select_t<T1, T2>::advice_type& _advice(T1&, T2& t2, int_<2> ) 
  {
    return t2.get_aspect().template get<Tg>();
  }

  template<typename T1, typename T2, typename T3>
  typename select_t<T1, T2, T3>::advice_type& _advice(T1& t1, T2& , T3&, int_<1> ) 
  {
    return t1.get_aspect().template get<Tg>();
  }

  template<typename T1, typename T2, typename T3>
  typename select_t<T1, T2, T3>::advice_type& _advice(T1&, T2& t2, T3&, int_<2> ) 
  {
    return t2.get_aspect().template get<Tg>();
  }

  template<typename T1, typename T2, typename T3>
  typename select_t<T1, T2, T3>::advice_type& _advice(T1&, T2&, T3& t3, int_<3> ) 
  {
    return t3.get_aspect().template get<Tg>();
  }
};

template<typename Tg, typename T1, typename T2>
typename switch_by_tag_t<Tg>::template select_t<T1, T2>::type& 
switch_by_tag(T1& t1, T2& t2) 
{
  return switch_by_tag_t<Tg>()(t1, t2); 
}

template<typename Tg, typename T1, typename T2, typename T3>
typename switch_by_tag_t<Tg>::template select_t<T1, T2, T3>::type& 
switch_by_tag(T1& t1, T2& t2, T3& t3) 
{
  return switch_by_tag_t<Tg>()(t1, t2, t3); 
}


}

#endif

