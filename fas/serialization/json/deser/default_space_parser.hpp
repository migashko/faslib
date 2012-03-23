#ifndef FAS_SERIALIZATION_JSON_DESER_DEFAULT_SPACE_PARSER_HPP
#define FAS_SERIALIZATION_JSON_DESER_DEFAULT_SPACE_PARSER_HPP

#include <fas/serialization/json/parser/ad_space.hpp>

namespace fas { namespace json{ namespace deser{
  
struct default_space_parser
{
  template<typename R>
  R operator()(R r) const
  {
    // TDOD: сделать функции для парсера
    parser::ad_space ads;
    return ads.parse(r);
  }
};

}}}

#endif

