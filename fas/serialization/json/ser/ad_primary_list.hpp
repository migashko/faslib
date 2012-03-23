#ifndef FAS_SERIALIZATION_JSON_SER_AD_PRIMARY_LIST_HPP
#define FAS_SERIALIZATION_JSON_SER_AD_PRIMARY_LIST_HPP

#include <fas/serialization/json/except/try_throw.hpp>
#include <fas/serialization/json/except/out_of_range.hpp>

#include <fas/type_list/type_list.hpp>
#include <fas/type_list/empty_list.hpp>

namespace fas{ namespace json{ namespace ser{

struct ad_primary_list
{
  template<typename T, typename M, typename V>
  bool check(T& t, M, const V& v)
  {
    typedef typename M::target_list target_list;
    return _check(t, M(), v, target_list() );
  };

  template<typename T, typename M, typename V, typename R>
  R operator()(T& t, M, const V& v, R r)
  {
    typedef typename M::target_list target_list;
    return _(t, M(), v, r, target_list(), true);
  }

private:
  template<typename T, typename M, typename V, typename R>
  R _(T&, M, const V&, R r, empty_list, bool)
  {
    return r;
  }

#ifndef DISABLE_TYPE_LIST_SPEC
  template<typename T, typename M, typename V, typename R, typename H, typename L >
  R _(T& t, M, const V& v, R r, type_list<H, L>, bool first )
  {
    typedef typename H::serializer_tag serializer_tag;
    if ( t.get_aspect().template get<serializer_tag>().check(t, H(), v) )
    {
      if ( first )
        first = false;
      else
      {
        if ( !r )
          return throw_(t, out_of_range(), r);

        *(r++)=',';
      }
      
      r = t.get_aspect().template get<serializer_tag>()(t, H(), v, r );

      if ( !try_(t) )
        return r;
    }
    
    return _(t, M(), v, r, L(), first);
  }
#endif // DISABLE_TYPE_LIST_SPEC

  template<typename T, typename M, typename V, typename R, typename L >
  R _(T& t, M, const V& v, R r, L, bool first )
  {
    typedef typename L::left_type head;
    typedef typename L::right_type tail;
    typedef typename head::serializer_tag serializer_tag;

    if ( t.get_aspect().template get<serializer_tag>().check(t, head(), v) )
    {
      if ( first )
        first = false;
      else
      {
        if ( !r )
          return throw_(t, out_of_range(), r);

        *(r++)=',';
      }
      r = t.get_aspect().template get<serializer_tag>()(t, head(), v, r );

      if ( !try_(t) )
        return r;
    }
    
    return _(t, M(), v, r, tail(), first);
  }

///
  template<typename T, typename M, typename V>
  bool _check(T& t, M, const V& v, empty_list)
  {
    return false;
  }

#ifndef DISABLE_TYPE_LIST_SPEC

  template<typename T, typename M, typename V, typename H, typename L >
  bool _check(T& t, M, const V& v, type_list<H, L> )
  {
    typedef typename H::serializer_tag serializer_tag;
    return 
      t.get_aspect().template get<serializer_tag>().check(t, H(), v)
      || _check(t, M(), v,  L() );
  }
  
#endif // DISABLE_TYPE_LIST_SPEC

  template<typename T, typename M, typename V, typename L >
  bool _check(T& t, M, const V& v, L )
  {
    typedef typename L::left_type head;
    typedef typename L::right_type tail;
    typedef typename head::serializer_tag serializer_tag;

    return 
      t.get_aspect().template get<serializer_tag>().check(t, head(), v) 
      || _check(t, M(), v,  tail() );
  }
};


}}}

#endif
