#ifndef FAS_SERIALIZATION_JSON_META_SECOND_HPP
#define FAS_SERIALIZATION_JSON_META_SECOND_HPP

#include <fas/typemanip/const_if_const.hpp>

namespace fas{ namespace json{

struct second
{
  template<typename T>
  typename const_if_const<typename T::second_type, T>::type&
  operator() (T& t)
  {
    return t.second;
  }
};

}}

#endif
