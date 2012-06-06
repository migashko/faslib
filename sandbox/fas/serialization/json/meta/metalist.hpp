// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_SERIALIZATION_JSON_METALIST_HPP
#define FAS_SERIALIZATION_JSON_METALIST_HPP

namespace fas{ namespace json{

/** Список метатипов */
namespace metalist
{
  struct number;
  struct string;
  struct boolean;
  struct object;
  struct array;
  struct any;  // for user define
  
  struct field;
  struct sequence;
}

}}

#endif
