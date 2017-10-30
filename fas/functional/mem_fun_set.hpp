//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2012, 2013
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_FUNCTIONAL_MEM_FUN_SET_HPP
#define FAS_FUNCTIONAL_MEM_FUN_SET_HPP

#include <fas/typemanip/remove_const_reference.hpp>

namespace fas{

template<typename V, typename VT, void (V::* mg)(VT), typename VVT = typename remove_const_reference<VT>::type >
struct mem_fun_set
{
  typedef VVT value_type;

  // cppcheck-suppress uninitMemberVar  
  mem_fun_set()
    : _obj()
    , _value()
  {}

  mem_fun_set(const mem_fun_set& mfs)
    : _obj(mfs._obj)
    , _value(mfs._value)
  {}

  mem_fun_set& operator=(const mem_fun_set& mfs)
  {
    _obj = mfs._obj;
    _value = mfs._value;
    return *this;
  }

  VVT& operator()(V& v)
  {
    _obj = &v;
    return _value;
  }

  ~mem_fun_set()
  {
    if ( _obj )
      (_obj->*mg)(_value);
  }

private:
  V*  _obj;
  VVT _value;
};

template<typename V, typename VT, void (V::* mg)(VT), typename VVT >
struct mem_fun_set<V, VT, mg, VVT*>
{
  typedef VVT value_type;

  
  mem_fun_set()
    : _obj()
    , _value()
  {
  }
  
  mem_fun_set(const mem_fun_set& mfs)
    : _obj(mfs._obj)
    , _value(mfs._value)
  {}

  mem_fun_set& operator=(const mem_fun_set& mfs)
  {
    _obj = mfs._obj;
    _value = mfs._value;
    return *this;
  }


  VVT* operator()(V& v, VVT* buffer )
  {
    _obj = &v;
    _value = buffer;
    return _value;
  }

  ~mem_fun_set()
  {
    if ( _obj )
      (_obj->*mg)(_value);
  }

private:
  V*  _obj;
  VVT* _value;
};

}

#endif
