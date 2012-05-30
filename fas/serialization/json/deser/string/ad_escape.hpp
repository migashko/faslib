#ifndef FAS_SERIALIZATION_JSON_DESER_STRING_AD_ESCAPE_HPP
#define FAS_SERIALIZATION_JSON_DESER_STRING_AD_ESCAPE_HPP

#include <fas/serialization/json/deser/tags.hpp>
#include <fas/serialization/json/except/tags.hpp>
#include <fas/serialization/common/deser/ad_json_escape_t.hpp>

namespace fas{ namespace json{ namespace deser{

struct ad_escape:
	::fas::serialization::deser::ad_json_escape_t<_uhex_, _except_>
{
	
};

}}}

#endif
