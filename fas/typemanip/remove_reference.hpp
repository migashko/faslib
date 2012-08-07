//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TYPEMANIP_REMOVE_REFERENCE_HPP
#define FAS_TYPEMANIP_REMOVE_REFERENCE_HPP

namespace fas{

template<typename T>
struct remove_reference
{
  typedef T type;
};

template<typename T>
struct remove_reference<T&>
{
  typedef typename remove_reference<T>::type type;
};


}

#endif
