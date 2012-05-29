#ifndef FAS_SERIALIZATION_JSON_META_GETSET_HPP
#define FAS_SERIALIZATION_JSON_META_GETSET_HPP

#include <fas/serialization/json/ser/tags.hpp>
#include <fas/serialization/json/deser/tags.hpp>
#include <fas/serialization/json/meta/metalist.hpp>

#include <fas/typemanip/remove_cvrp.hpp>
#include <fas/typemanip/empty_type.hpp>

namespace fas{ namespace json{

	/*
template<typename V, typename VT, VT (V::* mg)(void), void (V::* ms)(VT), typename M>
struct getset
{
  typedef M target;

  typedef typename M::metatype metatype;

  typedef ser::_getter_ serializer_tag;
  typedef deser::_setter_ deserializer_tag;

  // typedef VT value_type;
  typedef typename remove_cvrp<VT>::type value_type;

  VT get(const V& v) const
  {
    return (v.*mg)();
  }

  void set(V& v, VT value) const
  {
    (v.*ms)(value);
  }
};
*/

	
template<typename V, typename VT, VT (V::* mg)(void), void (V::* ms)(VT), typename M>
struct getset
{
  typedef M target;
  
  typedef typename M::metatype metatype;
  
  typedef ser::_getter_ serializer_tag;
  typedef deser::_setter_ deserializer_tag;
  
  // typedef VT value_type;
  typedef typename remove_cvrp<VT>::type value_type;

  VT get(const V& v) const
  {
    return (v.*mg)();
  }

  void set(V& v, VT value) const
  {
    (v.*ms)(value);
  }
};


template< typename VT, typename FG, typename FS, typename M = empty_type>
struct getset_f
{
  typedef M target;
  typedef typename M::metatype metatype;
  
  typedef ser::_prop_ serializer_tag;
  typedef deser::_prop_ deserializer_tag;
  
  // typedef VT value_type;
  typedef typename remove_cvrp<VT>::type value_type;

  template<typename V>
  VT get(const V& v) const
  {
    return FG()(v);
  }

  template<typename V>
  void set(V& v, VT value) const
  {
    FS()(v, value);
  }
};

template< typename VT, typename F, typename M>
struct getset_f<VT, F, M, empty_type>
{
  typedef M target;
  typedef typename M::metatype metatype;

  typedef ser::_prop_ serializer_tag;
  typedef deser::_prop_ deserializer_tag;

  // typedef VT value_type;
  typedef typename remove_cvrp<VT>::type value_type;

  template<typename V>
  VT get(const V& v) const
  {
    return F()(v);
  }

  template<typename V>
  void set(V& v, VT value) const
  {
    F()(v, value);
  }
};


}}

#endif
