//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2012
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_RANGE_IS_STREAM_HPP
#define FAS_RANGE_IS_STREAM_HPP

#include <ios>

#include <fas/typemanip/super_subclass.hpp>


namespace fas{

template<typename T>
struct is_stream
 : super_subclass<std::ios_base, T >
{
  
};

}

#endif
