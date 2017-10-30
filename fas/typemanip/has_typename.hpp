//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TYPEMANIP_HAS_TYPENAME_HPP
#define FAS_TYPEMANIP_HAS_TYPENAME_HPP

#define FAS_HAS_TYPENAME(N, D)\
namespace N##_detail{\
struct N##_helper {\
  typedef char small_type;\
  typedef struct big_tag { \
    char dummy[2]; \
  } big_type;\
  template<typename P>\
  static small_type test(typename P::D const *);\
  template<typename P>\
  static big_type test(...);\
}; \
template<typename T, bool>\
struct get_type;\
template<typename T>\
struct get_type<T, false>{typedef void type; };\
template<typename T>\
struct get_type<T, true>{ typedef typename T::D type; };\
} \
template<typename T>\
struct N\
{\
  typedef N##_detail::N##_helper helper; \
  enum { value = sizeof( helper::test<T>(0) ) == sizeof(helper::small_type) };\
  typedef typename N##_detail::get_type<T, value>::type type;\
};

#endif
