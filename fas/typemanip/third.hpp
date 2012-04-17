//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TYPEMANIP_THIRD_HPP
#define FAS_TYPEMANIP_THIRD_HPP

namespace fas{

template<typename P>
struct third
{
  typedef typename P::third type;
};

}

#endif
