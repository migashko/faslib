#ifndef FAS_SERIALIZATION_JSON_SERIALIZER_F_ITEM_SERIALIZE_HPP
#define FAS_SERIALIZATION_JSON_SERIALIZER_F_ITEM_SERIALIZE_HPP

namespace fas{ namespace json{ namespace ser{

template<typename T, typename M>
struct f_item_serialize
{
  typedef M meta_type;
  //typedef typename meta_type::item_metatype item_meta_type;
  typedef typename meta_type::serializer_tag serializer_tag;

  T& t;
  f_item_serialize(T& t): t(t){}

  template<typename V, typename R>
  R operator()(const V& v, R r)
  {
    return t.get_aspect().template get<serializer_tag>()(t, meta_type(), v, r);
  }
};

}}}

#endif
