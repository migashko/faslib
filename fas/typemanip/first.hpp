//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TYPEMANIP_FIRST_HPP
#define FAS_TYPEMANIP_FIRST_HPP

namespace fas{

template<typename P>
struct first
{
  typedef typename P::first type;
};

}

#endif
