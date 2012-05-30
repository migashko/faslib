#ifndef FAS_SERIALIZATION_JSON_DESER_STRING_AD_UTF8_HPP
#define FAS_SERIALIZATION_JSON_DESER_STRING_AD_UTF8_HPP

#include <fas/serialization/common/deser/ad_utf8_t.hpp>
#include <fas/serialization/json/except/tags.hpp>


namespace fas{ namespace json{ namespace deser{

struct ad_utf8:
	::fas::serialization::deser::ad_utf8_t<_except_>
{

};


}}}

#endif
