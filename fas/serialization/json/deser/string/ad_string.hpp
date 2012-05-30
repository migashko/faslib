#ifndef FAS_SERIALIZATION_JSON_DESER_STRING_AD_STRING_HPP
#define FAS_SERIALIZATION_JSON_DESER_STRING_AD_STRING_HPP

#include <fas/serialization/json/deser/tags.hpp>
#include <fas/serialization/json/parser/tags.hpp>
#include <fas/serialization/json/except/tags.hpp>

#include <fas/serialization/common/deser/ad_json_string_t.hpp>

namespace fas{ namespace json{ namespace deser{

struct ad_string:
	::fas::serialization::deser::ad_json_string_t<_string_content_, _quote_, parse::_string_, parse::_null_, _except_>
{
};

}}}

#endif
