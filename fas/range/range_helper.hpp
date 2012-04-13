//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2012
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_RANGE_RANGE_HELPER_HPP
#define FAS_RANGE_RANGE_HELPER_HPP

namespace fas{

template< typename T, int  >
struct range_helper;

}

#include <fas/range/detail/range_helper_other.hpp>
#include <fas/range/detail/range_helper_array.hpp>
#include <fas/range/detail/range_helper_pointer.hpp>
#include <fas/range/detail/range_helper_iterator.hpp>
#include <fas/range/detail/range_helper_container.hpp>
#include <fas/range/detail/range_helper_range.hpp>
#include <fas/range/detail/range_helper_stream.hpp>

#endif

