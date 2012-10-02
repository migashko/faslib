//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2012
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TYPEMANIP_REMOVE_CONST_REFERENCE_HPP
#define FAS_TYPEMANIP_REMOVE_CONST_REFERENCE_HPP

namespace fas{

template<typename T>
struct remove_const_reference
{
  typedef T type;
};

template<typename T>
struct remove_const_reference<const T>
{
  typedef typename remove_const_reference<T>::type type;
};

template<typename T>
struct remove_const_reference<const T*>
{
  typedef typename remove_const_reference<T*>::type type;
};

template<typename T>
struct remove_const_reference<T&>
{
  typedef typename remove_const_reference<T>::type type;
};

template<typename T>
struct remove_const_reference<const T&>
{
  typedef typename remove_const_reference<T>::type type;
};


}

#endif
