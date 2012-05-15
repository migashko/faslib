//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2012
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_SERIALIZATION_COMMON_EXCEPT_AD_EXCEPT_HPP
#define FAS_SERIALIZATION_COMMON_EXCEPT_AD_EXCEPT_HPP

#include <string>
#include <fas/serialization/common/except/common_error.hpp>

namespace fas{ namespace serialization{

struct ad_except
{
  
  template<typename T>
  void clear(T&) {}
  
  operator bool () const { return false;}

  template<typename T>
  void operator()(T&, const common_error& e)
  {
    throw e;
  }

  template<typename T, typename R>
  R operator()(T&, const common_error& e, R )
  {
    throw e;
  }
  
  std::string what() const
  {
    return std::string();
  }

  template<typename R>
  std::string message(R) const
  {
    return std::string();
  }

  common_error exception() const
  {
    return common_error("", 0);
  }

};

}}

#endif
