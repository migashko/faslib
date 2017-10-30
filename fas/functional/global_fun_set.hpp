//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2012, 2013
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_FUNCTIONAL_GLOBAL_FUN_SET_HPP
#define FAS_FUNCTIONAL_GLOBAL_FUN_SET_HPP

#include <fas/typemanip/remove_const_reference.hpp>

namespace fas{

template<typename V, typename VT, void (*fun)(V, VT), typename VVT = typename remove_const_reference<VT>::type>
struct global_fun_set
{
  // cppcheck-suppress uninitMemberVar  
  global_fun_set()
    : _obj()
    , _value() 
  {}

  // cppcheck-suppress uninitMemberVar  
  global_fun_set(const global_fun_set& gfs)
    : _obj(gfs._obj)
    , _value(gfs._value)
  {}

  // cppcheck-suppress uninitvar  
  global_fun_set& operator=(const global_fun_set& gfs)
  {
    this->_obj = gfs._obj;
    this->_value = gfs._value;
    return *this;
  }

  VVT& operator()(typename remove_const_reference<V>::type& v)
  {
    _obj = &v;
    return _value;
  }

  ~global_fun_set()
  {
    if ( _obj )
      (*fun)( *_obj, _value);
  }

private:
  typename remove_const_reference<V>::type*  _obj;
  VVT _value;
};

template<typename V, typename VT, void (*fun)(V, VT), typename VVT >
struct global_fun_set<V, VT, fun, VVT*>
{
  global_fun_set()
    : _obj()
    , _value() 
  {}

  // cppcheck-suppress uninitMemberVar  
  global_fun_set(const global_fun_set& gfs)
    : _obj(gfs._obj)
    , _value(gfs._value)
  {}

  // cppcheck-suppress uninitvar  
  global_fun_set& operator=(const global_fun_set& gfs)
  {
    this->_obj = gfs._obj;
    this->_value = gfs._value;
    return *this;
  }
  
  VVT* operator()(typename remove_const_reference<V>::type& v, VVT* buffer)
  {
    _obj = &v;
    _value = buffer;
    return _value;
  }

  ~global_fun_set()
  {
    if ( _obj )
      (*fun)( *_obj, _value);
  }

private:
  typename remove_const_reference<V>::type*  _obj;
  VVT* _value;
};

}

#endif
