//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2012
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_RANGE_ADVANCE_HPP
#define FAS_RANGE_ADVANCE_HPP

#include <fas/range/typerange.hpp>

namespace fas{

template<typename R, typename Dist>
inline void advance(R& r, Dist s)
{
   typerange<R>::advance(r, s);
}

}

#endif
