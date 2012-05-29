#ifndef FAS_SERIALIZATION_JSON_META_OBJECT_HPP
#define FAS_SERIALIZATION_JSON_META_OBJECT_HPP

/*
#include <fas/serialization/json/ser/tags.hpp>
#include <fas/serialization/json/deser/tags.hpp>
#include <fas/serialization/json/meta/stub.hpp>
#include <fas/serialization/has_serializer_tag.hpp>
#include <fas/serialization/json/meta/field_list.hpp>
#include <fas/typemanip/empty_type.hpp>
#include <fas/typemanip/if_c.hpp>
#include <fas/static_check/static_check.hpp>
#include <fas/type_list/empty_list.hpp>
#include <fas/type_list/type_list.hpp>
#include <fas/type_list/is_type_list.hpp>
*/

#include <fas/serialization/json/ser/tags.hpp>
#include <fas/serialization/json/deser/tags.hpp>

#include <fas/serialization/json/meta/stub.hpp>
#include <fas/serialization/has_serializer_tag.hpp>

#include <fas/serialization/json/meta/primary_list.hpp>
#include <fas/serialization/json/meta/sequence.hpp>
#include <fas/typemanip/empty_type.hpp>
#include <fas/typemanip/if_c.hpp>
#include <fas/static_check/static_check.hpp>
#include <fas/type_list/empty_list.hpp>
#include <fas/type_list/type_list.hpp>
#include <fas/type_list/is_type_list.hpp>

#include <fas/type_list/type_list_n.hpp>
#include <fas/typemanip/switch_.hpp>
#include <fas/typemanip/case_.hpp>
#include <fas/typemanip/default_.hpp>
#include <fas/integral/bool_.hpp>
#include <fas/serialization/json/meta/metalist.hpp>

namespace fas{ namespace json{
  
  /*
namespace detail{

  
template<typename T>
struct object_helper
{
 typedef typename switch_< 
    typename type_list_n<
      case_< some_type<T, stub>, stub >,
      case_< is_type_list<T>, field_list<T> >,
      case_< has_serializer_tag<T>, T >,
      case_< has_deserializer_tag<T>, T >,
      default_< empty_type >
    >::type
  >::type type;

  typedef typename switch_< 
    typename type_list_n<
      case_< some_type<T, stub>, stub >,
      case_< is_type_list<T>, field_list2<T> >,
      case_< has_serializer_tag<T>, T >,
      case_< has_deserializer_tag<T>, T >,
      default_< empty_type >
    >::type
  >::type type2;

};

  
}
*/

template<typename L>
struct object
{
  typedef metalist::object metatype;
  typedef typename if_c< is_type_list<L>::value, primary_list<L>, L >::type target;
  
  typedef ser::_object_ serializer_tag;
  typedef deser::_object_ deserializer_tag;
  /*
  typedef typename detail::object_helper<F>::type target1;
  typedef typename detail::object_helper<S>::type2 target2;

  typedef ser::_object_ serializer_tag;
  typedef deser::_object_ deserializer_tag;
  */
};


}}

#endif
