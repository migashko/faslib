#ifndef FAS_SERIALIZATION_JSON_META_ATTR_HPP
#define FAS_SERIALIZATION_JSON_META_ATTR_HPP

#include <fas/serialization/json/ser/tags.hpp>
#include <fas/serialization/json/deser/tags.hpp>

#include <fas/typemanip/remove_cvrp.hpp>

namespace fas{ namespace json{

template<typename V, typename VT, VT V::* m, typename M>
struct attr
{
  typedef typename M::metatype metatype;
  typedef M target;
  typedef ser::_attr_ serializer_tag;
  typedef deser::_attr_ deserializer_tag;
  
  // typedef VT value_type;
  typedef typename remove_cvrp<VT>::type value_type;

  VT& ref(V& v) const
  {
    return v.*m;
  }

  const VT& ref(const V& v) const
  {
    return v.*m;
  }
};

template<typename VT, typename FG, typename FS,  typename M = empty_type>
struct field
{
  typedef typename M::metatype metatype;
  typedef M target;
  typedef ser::_attr_ serializer_tag;
  typedef deser::_attr_ deserializer_tag;

  // typedef VT value_type;
  typedef typename remove_cvrp<VT>::type value_type;

  template<typename V>
  const VT& ref(const V& v) const
  {
    return FG()(v);
  }

  template<typename V>
  VT& ref(V& v) const
  {
    return FS()(v);
  }
};

template<typename VT, typename F, typename M >
struct field<VT, F, M, empty_type>
{
  typedef typename M::metatype metatype;
  typedef M target;
  typedef ser::_attr_ serializer_tag;
  typedef deser::_attr_ deserializer_tag;

  // typedef VT value_type;
  typedef typename remove_cvrp<VT>::type value_type;

  template<typename V>
  const VT& ref(const V& v) const
  {
    return F()(v);
  }

  template<typename V>
  VT& ref(V& v) const
  {
    return F()(v);
  }
};

}}

#endif
