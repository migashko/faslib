#ifndef FAS_SERIALIZATION_COMMON_PARSER_AD_JSON_NULL_T_HPP
#define FAS_SERIALIZATION_COMMON_PARSER_AD_JSON_NULL_T_HPP

#include <fas/serialization/common/parser/ad_cstring_list_t.hpp>
#include <fas/typemanip/tchars.hpp>


namespace fas{ namespace serialization{ namespace parse{
	
template<typename TgExcept>
struct ad_json_null_t: ad_cstring_list_t< tchars<'n', 'u', 'l', 'l'>, TgExcept >
{};

}}}

#endif
