#ifndef FAS_SERIALIZATION_JSON_META_DICT_HPP
#define FAS_SERIALIZATION_JSON_META_DICT_HPP

#include <fas/serialization/json/meta/attr.hpp>
#include <fas/serialization/json/meta/member.hpp>
#include <fas/serialization/json/meta/sequence.hpp>
#include <fas/serialization/json/meta/object.hpp>

#include <fas/serialization/json/meta/raw.hpp>
#include <fas/serialization/json/meta/string.hpp>

#include <string>


namespace fas{ namespace json{

struct f_dict_first
{
  template<typename T>
  typename T::first_type& operator() (T& t)
  {
    return t.first;
  }
};

struct f_dict_second
{
  template<typename T>
  typename T::second_type& operator() (T& t)
  {
    return t.second;
  }

  template<typename T>
  const typename T::second_type& operator() (const T& t)
  {
    return t.second;
  }

};

template<typename KV, typename KM, typename VT, typename VM>
struct make_dict
{
  typedef field< KV, f_dict_first, KM> key_type;
  typedef field< VT, f_dict_second, VM> mapped_type;
  typedef member< key_type, mapped_type> member_type;
  typedef sequence< member_type > sequence_type;
  typedef object< sequence_type > type;
};


template<typename VT = std::string, typename M = raw >
struct dict: make_dict< std::string, string, VT, M >::type { };

template<typename VT  = std::wstring , typename M = raw >
struct wdict: make_dict< std::wstring, string, VT, M >::type { };


}}

#endif
