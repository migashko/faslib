//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TYPEMANIP_SECOND_HPP
#define FAS_TYPEMANIP_SECOND_HPP

namespace fas{

template<typename P>
struct second
{
  typedef typename P::second type;
};

}

#endif
