// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TYPEMANIP_REMOVE_CVPR_HPP
#define FAS_TYPEMANIP_REMOVE_CVPR_HPP

namespace fas{

template<typename T>
struct remove_cvrp
{
  typedef T type;
};

template<typename T>
struct remove_cvrp<const T>
{
  typedef typename remove_cvrp<T>::type type;
};

template<typename T>
struct remove_cvrp<volatile T>
{
  typedef typename remove_cvrp<T>::type type;
};

template<typename T>
struct remove_cvrp<const volatile T>
{
  typedef typename remove_cvrp<T>::type type;
};

template<typename T>
struct remove_cvrp<T*>
{
  typedef typename remove_cvrp<T>::type type;
};

template<typename T>
struct remove_cvrp<T&>
{
  typedef typename remove_cvrp<T>::type type;
};

}

#endif
