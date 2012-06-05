//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011, 2012
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_RANGE_IRANGE_HPP
#define FAS_RANGE_IRANGE_HPP

#include <fas/range/typerange.hpp>
#include <fas/range/range_adapter.hpp>
#include <fas/range/range.hpp>

namespace fas{

template<typename InputContainer, typename OutputContainer>
inline
input_range_adapter<
  typename typerange<InputContainer>::range,
  OutputContainer
>
irange(InputContainer& in_cnt, OutputContainer& out_cnt )
{
  return input_range_adapter< typename typerange<InputContainer>::range, OutputContainer>( range(in_cnt), out_cnt );
}

template<typename InputRange, typename OutputRange>
inline
copy_range_adapter<InputRange, OutputRange>
crange(InputRange ri, OutputRange ro)
{
  return copy_range_adapter<InputRange, OutputRange>( ri, ro);
}

}

#endif
