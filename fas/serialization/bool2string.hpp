#ifndef FAS_SERIALIZATION_BOOL2STRING_HPP
#define FAS_SERIALIZATION_BOOL2STRING_HPP

#include <fas/range/string_range.hpp>
#include <fas/typemanip/tstring.hpp>

namespace fas {
  
FAS_NAME(true)
FAS_NAME(false)

template<typename T = n_true, typename F = n_false>
class bool2string
{
public:
  typedef string_range<const char*> range_type;
  
  bool2string():_value(false){}
  
  explicit bool2string(bool value):_value(value){}
  
  void operator = (bool value)
  {
    _value = value;
  }
  
  operator const char* () const
  {
    return _value ? T()() : F()();
  }

  const char* c_str() const
  {
    return _value ? T()() : F()();
  }

  operator range_type () const
  {
    return _value ? range_type(T()()) : range_type(F()());
  }
  
  range_type get_range() const
  {
    return _value ? range_type(T()()) : range_type(F()());
  }
  
private:
  
  bool _value;
  
};

}

#endif
