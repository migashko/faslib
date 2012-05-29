#ifndef FAS_DESER_JSON_DESER_AD_PRIMARY_LIST_HPP
#define FAS_DESER_JSON_DESER_AD_PRIMARY_LIST_HPP

#include <fas/serialization/common/deser/ad_primary_list_t.hpp>

#include <fas/serialization/json/parser/tags.hpp>
#include <fas/serialization/json/deser/tags.hpp>

namespace fas{ namespace json{ namespace deser{

struct ad_primary_list: 
  ::fas::serialization::deser::ad_primary_list_t< _separator_, parse::_space_, parse::_item_>
{};

}}}

#endif
