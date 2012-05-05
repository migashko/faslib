#ifndef FAS_SERIALIZATION_JSON_META_DICT_HPP
#define FAS_SERIALIZATION_JSON_META_DICT_HPP

#include <fas/serialization/json/meta/field.hpp>
#include <fas/serialization/json/meta/member.hpp>
#include <fas/serialization/json/meta/sequence.hpp>
#include <fas/serialization/json/meta/object.hpp>

#include <fas/serialization/json/meta/raw.hpp>
#include <fas/serialization/json/meta/string.hpp>
#include <fas/serialization/json/meta/first.hpp>
#include <fas/serialization/json/meta/second.hpp>

#include <string>


namespace fas{ namespace json{

template<typename KV, typename KM, typename VT, typename VM>
struct dict_helper
{
  typedef field< KV, first, KM> key_type;
  typedef field< VT, second, VM> mapped_type;
  typedef member< key_type, mapped_type> member_type;
  typedef sequence< member_type > sequence_type;
  typedef object< sequence_type > type;
};

template<typename VT = std::string, typename M = raw >
struct dict: dict_helper< std::string, string, VT, M >::type { };

template<typename VT  = std::wstring , typename M = raw >
struct wdict: dict_helper< std::wstring, string, VT, M >::type { };


}}

#endif
