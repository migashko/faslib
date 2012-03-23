// ага
// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TYPEMANIP_DETAIL_CONVERSION_HPP
#define FAS_TYPEMANIP_DETAIL_CONVERSION_HPP

namespace fas{ namespace detail{

struct conversion_base
{
  typedef char small_type;
  typedef class big_tag { char dummy[2];} big_type;
};

template<typename T, typename U>
struct conversion_helper
  : conversion_base
{
  static small_type test(U);
  static big_type test(...);
  static T makeT();
};

}}

#endif
