//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2012
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_SERIALIZATION_COMMON_EXCEPT_AD_EMPTYEXCEPT_HPP
#define FAS_SERIALIZATION_COMMON_EXCEPT_AD_EMPTYEXCEPT_HPP

#include <string>
#include <fas/serialization/common/except/common_error.hpp>

namespace fas{ namespace serialization{

class ad_emptyexcept
{
  
public:
  
  ad_emptyexcept()
    : _except(false)
  {
    _except = false;
  }
  
  template<typename T>
  void clear(T&) 
  {
    _except = false; 
  }
  
  operator bool () const
  {
    return _except;
  }

  template<typename T>
  void operator()(T&, const common_error& e )
  {
    _except = true;
  }

  template<typename T, typename R>
  R operator()(T&, const common_error& e, R r )
  {
    _except = true;
    return r;
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


private:
  bool _except;
};

}}

#endif
