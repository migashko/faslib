#ifndef FAS_SERIALIZATION_COMMON_PARSER_AD_JSON_BOOLEAN_T_HPP
#define FAS_SERIALIZATION_COMMON_PARSER_AD_JSON_BOOLEAN_T_HPP

#include <fas/serialization/common/parse/ad_cstring_list_t.hpp>
#include <fas/typemanip/tchars.hpp>


namespace fas{ namespace serialization{ namespace parse{
	
template<typename TgExcept>
struct ad_json_boolean_t: ad_cstring_list_t< 
  type_list_n<
    tchars<'t', 'r', 'u', 'e'>,
    tchars<'f', 'a', 'l', 's', 'e'> 
  >::type,
	TgExcept
>
{};

}}}

#endif
