#ifndef FAS_SERIALIZATION_JSON_DESER_AD_STRING_HPP
#define FAS_SERIALIZATION_JSON_DESER_AD_STRING_HPP


#include <fas/serialization/json/deser/string/ad_uhex.hpp>
#include <fas/serialization/json/deser/string/ad_utf8.hpp>
#include <fas/serialization/json/deser/string/ad_escape.hpp>
#include <fas/serialization/json/deser/string/ad_string_content.hpp>
#include <fas/serialization/json/deser/string/ad_string.hpp>
#include <fas/serialization/json/deser/string/ad_cstring.hpp>
#include <fas/serialization/json/deser/string/ad_quote.hpp>

#include <fas/serialization/json/deser/tags.hpp>
#include <fas/serialization/json/parser/tags.hpp>

#include <fas/type_list/type_list_n.hpp>
#include <fas/aop/aspect.hpp>
#include <fas/aop/advice.hpp>

namespace fas{ namespace json{ namespace deser{


struct string_aspect:	aspect< type_list_n<
	advice< _uhex_, ad_uhex>,
	advice< _utf8_, ad_utf8>,
	advice< _escape_, ad_escape>,
	advice< _string_content_, ad_string_content>,
	advice< _string_, ad_string>,
	advice< _cstring_, ad_cstring>,
  advice< _quote_, ad_quote>
>::type> {};


}}}

#endif
