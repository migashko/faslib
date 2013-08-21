//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011, 2013
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_AOP_TAG_CAST_HPP
#define FAS_AOP_TAG_CAST_HPP

namespace fas{

template<typename T>
struct tag_cast
{
  typedef typename T::tag type;
};

}

#endif
