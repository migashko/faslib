#ifndef FAS_SERIALIZATION_JSON_EXCEPT_AD_EXCEPT_HPP
#define FAS_SERIALIZATION_JSON_EXCEPT_AD_EXCEPT_HPP

#include <string>

namespace fas{ namespace json{

struct ad_except
{
  
  template<typename T>
  void clear(T&) {}
  
  operator bool () const { return false;}

  template<typename T, typename E>
  void operator()(T&, const E& e)
  {
    throw e;
  }

  template<typename T, typename E, typename R>
  R operator()(T&, const E& e, R )
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

  json_error exception() const
  {
    return json_error("", 0);
  }

};

}}

#endif
