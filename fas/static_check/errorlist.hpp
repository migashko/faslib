//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_STATIC_CHECK_ERRORLIST_HPP
#define FAS_STATIC_CHECK_ERRORLIST_HPP

namespace fas{

namespace errorlist
{
  template<typename ERR>
  struct noerror { };

  struct type_without_metatype;
  struct bad_metatype;
  template<int I, int L>
  struct out_of_range;
}

}

#endif


