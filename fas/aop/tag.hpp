//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_AOP_TAG_HPP
#define FAS_AOP_TAG_HPP


namespace fas{

template<typename Tg>
struct tag
{
  typedef Tg type;
};

}

#endif
