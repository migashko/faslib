#ifndef FAS_SERIALIZATION_JSON_META_FIRST_HPP
#define FAS_SERIALIZATION_JSON_META_FIRST_HPP

#include <fas/typemanip/const_if_const.hpp>

namespace fas{ namespace json{

struct first
{
  template<typename T>
  typename const_if_const<typename T::first_type, T>::type&
  operator() (T& t)
  {
    return t.first;
  }
};


}}

#endif
