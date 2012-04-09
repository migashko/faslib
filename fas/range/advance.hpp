#ifndef FAS_RANGE_ADVANCE_HPP
#define FAS_RANGE_ADVANCE_HPP

#include <fas/range/typerange.hpp>
#include <cstddef>

namespace fas{

template<typename R>
inline void advance(R& r, typename typerange<R>::difference_type s)
{
   typerange<R>::advance(r, s);
}

}

#endif
