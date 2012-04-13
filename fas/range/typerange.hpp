//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2012
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_RANGE_TYPERANGE_HPP
#define FAS_RANGE_TYPERANGE_HPP

#include <fas/range/typerange_flag.hpp>
#include <fas/range/range_helper.hpp>

namespace fas{

template<typename T>
struct typerange
  : range_helper<T, typerange_flag::make<T>::value >
{
};

};

#endif
