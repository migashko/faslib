//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011, 2012
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_RANGE_CRANGE_HPP
#define FAS_RANGE_CRANGE_HPP

#include <fas/range/copy_range_adapter.hpp>

namespace fas{

template<typename InputRange, typename OutputRange>
inline
copy_range_adapter<InputRange, OutputRange>
crange(InputRange ri, OutputRange ro)
{
  return copy_range_adapter<InputRange, OutputRange>( ri, ro);
}

}

#endif
