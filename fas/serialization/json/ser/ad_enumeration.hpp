#ifndef FAS_SERIALIZATION_JSON_SER_AD_ENUMERATION_HPP
#define FAS_SERIALIZATION_JSON_SER_AD_ENUMERATION_HPP

#include <fas/serialization/json/except/try_throw.hpp>
#include <fas/serialization/json/except/out_of_range.hpp>

#include <fas/type_list/type_list.hpp>
#include <fas/type_list/empty_list.hpp>


namespace fas{ namespace json{ namespace ser{

struct ad_enumeration
{
  template<typename T, typename M, typename V>
  bool check(T&, M, V )
  {
    return true;
  };

  template<typename T, typename M, typename V, typename R>
  R operator()(T& t, M, V v, R r)
  {
    typedef typename M::target_list target_list;
    if ( !try_(t) )
      return r;

    
    return _(t, target_list(), v, r);
  }

private:
  
  template<typename T, typename EL, typename V, typename R>
  R _(T& t, EL, V v, R r)
  {
    return _(t, type_list<typename EL::left_type, typename EL::right_type>(), v, r);
  }

  template<typename T, typename EL, typename ER, typename V, typename R>
  R _(T& t, type_list<EL, ER>, V v, R r)
  {
    typedef typename EL::serializer_tag serializer_tag;
    
    if ( t.get_aspect().template get<serializer_tag>().check(t, EL(), v) )
      return t.get_aspect().template get<serializer_tag>()(t, EL(), v, r);
    
    return _(t, ER(), v, r);
  }

  template<typename T, typename V, typename R>
  R _(T& t, empty_list, V v, R r)
  {

    if ( !r )
      return throw_(t, out_of_range(), r);

    *(r++)='"';

    if ( !r )
      return throw_(t, out_of_range(), r);

    *(r++)='"';
    
    return r;
  }
  
};

}}}

#endif
