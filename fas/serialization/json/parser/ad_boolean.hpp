#ifndef FAS_SERIALIZATION_JSON_PARSER_AD_BOOLEAN_HPP
#define FAS_SERIALIZATION_JSON_PARSER_AD_BOOLEAN_HPP

#include <fas/serialization/common/parser/ad_json_boolean_t.hpp>
#include <fas/serialization/json/except/tags.hpp>

namespace fas{ namespace json{ namespace parse{
	
struct ad_boolean:
	::fas::serialization::parse::ad_json_boolean_t<_except_>
{};

}}}

#endif
