#ifndef FAS_SERIALIZATION_JSON_DESER_STRING_AD_STRING_CONTENT_HPP
#define FAS_SERIALIZATION_JSON_DESER_STRING_AD_STRING_CONTENT_HPP

#include <fas/serialization/json/deser/tags.hpp>
#include <fas/serialization/json/parser/tags.hpp>
#include <fas/serialization/json/except/tags.hpp>

#include <fas/serialization/common/deser/ad_jsonbase_string_t.hpp>

namespace fas{ namespace json{ namespace deser{

struct ad_string_content:
	::fas::serialization::deser::ad_jsonbase_string_t<_quote_, _utf8_, _escape_, _except_>
{
};

}}}

#endif
