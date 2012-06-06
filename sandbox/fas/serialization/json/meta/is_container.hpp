// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_SERIALIZATION_JSON_MEAT_IS_CONTAINER_HPP
#define FAS_SERIALIZATION_JSON_MEAT_IS_CONTAINER_HPP

#include <fas/serialization/json/meta/is_object.hpp>
#include <fas/serialization/json/meta/is_array.hpp>

namespace fas{ namespace json{

template<typename T>
struct is_container
{
  enum { value = is_object<T>::value || is_array<T>::value };
};


}}

#endif
