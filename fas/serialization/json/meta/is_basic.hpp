// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_SERIALIZATION_JSON_META_IS_BASIC_HPP
#define FAS_SERIALIZATION_JSON_META_IS_BASIC_HPP

#include <fas/serialization/json/meta/is_string.hpp>
#include <fas/serialization/json/meta/is_number.hpp>
#include <fas/serialization/json/meta/is_boolean.hpp>
#include <fas/serialization/json/meta/is_any.hpp>

namespace fas{ namespace json{

template<typename T>
struct is_basic
{
  enum { value = is_string<T>::value || is_number<T>::value || is_boolean<T>::value || is_any<T>::value };
};


}}

#endif
