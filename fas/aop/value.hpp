//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_AOP_VALUE_HPP
#define FAS_AOP_VALUE_HPP

namespace fas{

template<typename V>
struct value
{
  typedef V value_type;

  value()
    : _value()
  {}

  template<typename T>
  const value_type& operator()(T& ) const
  {
    return get_value();
  }

  template<typename T>
  void operator()(T&, const value_type& newval)
  {
    set_value(newval);
  }

  const value_type& get_value() const
  {
    return _value;
  }

  void set_value(const value_type& newval)
  {
    _value = newval;
  }

private:
  value_type _value;
};

}

#endif
