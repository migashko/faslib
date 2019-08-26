//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013-2015
//
// Copyright: See COPYING file that comes with this distribution
//

#pragma once

#include <memory>
#include <utility>

#if __cplusplus <= 201103
#ifndef DEF_MAKE_UNIQUE
#define DEF_MAKE_UNIQUE

namespace _dmu_{

template<class T>
struct _Unique_if
{
  typedef ::std::unique_ptr<T> _Single_object;
};

template<class T>
struct _Unique_if<T[]>
{
  typedef ::std::unique_ptr<T[]> _Unknown_bound;
};

template<class T, size_t N>
struct _Unique_if<T[N]>
{
  typedef void _Known_bound;
};

}

namespace std
{

template<class T, class... Args>
typename _dmu_::_Unique_if<T>::_Single_object
make_unique(Args&&... args)
{
  return unique_ptr<T>(new T(std::forward<Args>(args)...));
}

template<class T>
typename _dmu_::_Unique_if<T>::_Unknown_bound
make_unique(size_t n)
{
  typedef typename remove_extent<T>::type U;
  return unique_ptr<T>(new U[n]());
}

template<class T, class... Args>
typename _dmu_::_Unique_if<T>::_Known_bound
make_unique(Args&&...) = delete;

}

#endif
#endif
