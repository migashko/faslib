// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_SERIALIZATION_JSON_META_IS_SEQUENCE_HPP
#define FAS_SERIALIZATION_JSON_META_IS_SEQUENCE_HPP

#include <fas/typemanip/is_has_metatype.hpp>
#include <fas/serialization/json/meta/metalist.hpp>

namespace fas{ namespace json{

template<typename T>
struct is_sequence: is_has_metatype<T, metalist::sequence > {};

}}

#endif
