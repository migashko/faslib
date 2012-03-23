//
// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TYPEMANIP_FIFTH_HPP
#define FAS_TYPEMANIP_FIFTH_HPP



namespace fas{

template<typename P>
struct fifth
{
  typedef typename P::fifth type;
};

}

#endif
