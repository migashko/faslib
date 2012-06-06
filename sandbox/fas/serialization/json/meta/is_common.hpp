// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_SERIALIZATION_JSON_META_IS_COMMON_HPP
#define FAS_SERIALIZATION_JSON_META_IS_COMMON_HPP

#include <fas/serialization/json/meta/is_basic.hpp>
#include <fas/serialization/json/meta/is_container.hpp>


namespace fas{ namespace json{

template<typename T>
struct is_common
{
  enum { value = is_basic<T>::value || is_container<T>::value };
};



}}

#endif
