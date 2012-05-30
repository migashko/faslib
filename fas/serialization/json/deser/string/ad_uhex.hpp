#ifndef FAS_SERIALIZATION_JSON_DESER_STRING_AD_UHEX_HPP
#define FAS_SERIALIZATION_JSON_DESER_STRING_AD_UHEX_HPP

#include <fas/serialization/common/deser/ad_json_uhex_t.hpp>
#include <fas/serialization/json/except/tags.hpp>


namespace fas{ namespace json{ namespace deser{

struct ad_uhex:
	::fas::serialization::deser::ad_json_uhex_t<_except_>
{

};

}}}

#endif
