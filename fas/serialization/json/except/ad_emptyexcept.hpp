#ifndef FAS_SERIALIZATION_JSON_EXCEPT_AD_EMPTYEXCEPT_HPP
#define FAS_SERIALIZATION_JSON_EXCEPT_AD_EMPTYEXCEPT_HPP

#include <string>
#include <fas/serialization/json/except/json_error.hpp>

namespace fas{ namespace json{
  

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
  
  template<typename T, /*typename E,*/ typename R>
  R operator()(T&, const json_error& e, R r )
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

private:
  bool _except;
};

/*
struct ad_emptyexcept
{
  ad_emptyexcept()
    : _except(false)
  {
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
  
  template<typename T, typename E, typename R >
  R operator()(T&, const E&, R r)
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

private:
  bool _except;

};
*/

}}

#endif