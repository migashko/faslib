// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_SERIALIZATION_JSON_META_IS_OBJECT_HPP
#define FAS_SERIALIZATION_JSON_META_IS_OBJECT_HPP

#include <fas/typemanip/is_has_metatype.hpp>
#include <fas/serialization/json/meta/metalist.hpp>

namespace fas{ namespace json{

template<typename T>
struct is_object: is_has_metatype<T, metalist::object > {};

}}

#endif
