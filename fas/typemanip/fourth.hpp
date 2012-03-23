//
// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TYPEMANIP_FOURTH_HPP
#define FAS_TYPEMANIP_FOURTH_HPP

namespace fas{

template<typename P>
struct fourth
{
  typedef typename P::fourth type;
};

}

#endif
