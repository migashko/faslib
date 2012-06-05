#ifndef FAS_DESER_JSON_DESER_AD_SEPARATOR_HPP
#define FAS_DESER_JSON_DESER_AD_SEPARATOR_HPP

#include <fas/serialization/common/deser/ad_separator_t.hpp>
#include <fas/typemanip/tchars.hpp>

namespace fas{ namespace json{ namespace deser{

struct ad_comma: 
  ::fas::serialization::deser::ad_char_t< char, ',' >{};

/*struct ad_quotes: 
  ::fas::serialization::deser::ad_separator_t< tchars<'"'> >{};
  */

}}}

#endif
