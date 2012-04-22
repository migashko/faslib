//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TYPE_LIST_ERRORLIST_HPP
#define FAS_TYPE_LIST_ERRORLIST_HPP

namespace fas{

namespace errorlist
{
  struct noerror { };
  struct not_type_list;
  struct type_without_metatype;
  struct bad_metatype;
  struct not_organized;

  template<int I, int L>
  struct out_of_range;
};

}

#endif


