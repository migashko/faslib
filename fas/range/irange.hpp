//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011, 2012
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_RANGE_IRANGE_HPP
#define FAS_RANGE_IRANGE_HPP

#include <fas/range/typerange.hpp>
#include <fas/range/input_range_adapter.hpp>
#include <fas/range/range.hpp>

namespace fas{

template<typename InputContainer, typename SequenceContainer>
inline
input_range_adapter<
  typename typerange<InputContainer>::range,
  SequenceContainer
>
irange(InputContainer& in_cnt, SequenceContainer& out_cnt )
{
  return input_range_adapter< typename typerange<InputContainer>::range, SequenceContainer>( range(in_cnt), out_cnt );
}

}

#endif
