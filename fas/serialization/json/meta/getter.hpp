#ifndef FAS_SERIALIZATION_JSON_META_GETTER_HPP
#define FAS_SERIALIZATION_JSON_META_GETTER_HPP

#include <fas/serialization/json/ser/tags.hpp>
#include <fas/serialization/json/deser/tags.hpp>

#include <fas/serialization/json/meta/metalist.hpp>

#include <fas/typemanip/remove_cvrp.hpp>

namespace fas{ namespace json{


template<typename V, typename VT, VT (V::* m)(void) const, typename M>
struct getter
{
  typedef typename M::metatype metatype;
  typedef M target;
  
  typedef ser::_prop_ serializer_tag;
  typedef deser::_stub_ deserializer_tag;
  
  typedef typename remove_cvrp<VT>::type value_type;
  
  VT get(const V& v) const
  {
    return (v.*m)();
  }
};

template<typename VT, typename F, typename M>
struct getter_f
{
  typedef typename M::metatype metatype;
  typedef M target;

  typedef ser::_prop_ serializer_tag;
  typedef deser::_stub_ deserializer_tag;

  typedef typename remove_cvrp<VT>::type value_type;

  template<typename V>
  VT get(const V& v)
  {
    return F()(v);
  }
};


}}

#endif
