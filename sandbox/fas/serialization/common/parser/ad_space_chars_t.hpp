#ifndef FAS_SERIALIZATION_COMMON_PARSER_AD_SPACE_CHARS_T_HPP
#define FAS_SERIALIZATION_COMMON_PARSER_AD_SPACE_CHARS_T_HPP

#include <fas/serialization/common/parser/ad_char_list_t.hpp>
#include <fas/typemanip/tchars.hpp>

namespace fas{ namespace serialization{ namespace parse{

template<typename TgExcept>
struct ad_space_chars_t: ad_char_list_t< tchars<' ', '\t', '\r', '\n'>, TgExcept >
{};

}}}

#endif
