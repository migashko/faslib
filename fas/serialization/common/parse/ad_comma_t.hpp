#ifndef FAS_SERIALIZATION_COMMON_PARSER_AD_COMMA_T_HPP
#define FAS_SERIALIZATION_COMMON_PARSER_AD_COMMA_T_HPP

#include <fas/serialization/common/parse/ad_char_t.hpp>

namespace fas{ namespace serialization{ namespace parse{
	
template<typename TgExcept>
struct ad_comma_t: ad_char_t< char, ',', TgExcept >
{};

}}}

#endif
