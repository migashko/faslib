#ifndef FAS_DESER_JSON_DESER_STRING_AD_QUOTE_HPP
#define FAS_DESER_JSON_DESER_STRING_AD_QUOTE_HPP

#include <fas/serialization/common/deser/ad_separator_t.hpp>
#include <fas/typemanip/tchars.hpp>

namespace fas{ namespace json{ namespace deser{

struct ad_quote: 
  ::fas::serialization::deser::ad_separator_t< tchars<'"'> >{};

}}}

#endif
