//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TYPEMANIP_HAS_MEMBER_FUNCTION_HPP
#define FAS_TYPEMANIP_HAS_MEMBER_FUNCTION_HPP

#define FAS_HAS_MEMBER_FUNCTION0(N, D, R)\
namespace N##_detail{\
template < typename T, R (T::*)() > struct op_mf {}; \
struct N##_helper {\
  typedef char small_type;\
  typedef class big_tag { char dummy[2];} big_type;\
  template<typename P>\
  static small_type test(op_mf<P, &P::D>*);\
  template<typename P>\
  static big_type test(...);\
}; \
} \
template<typename T>\
struct N\
{\
  typedef N##_detail::N##_helper helper; \
  enum { value = sizeof( helper::test<T>(0) ) == sizeof(helper::small_type) };\
};

#define FAS_HAS_MEMBER_FUNCTION1(N, D, R, P1)\
namespace N##_detail{\
template < typename T, R (T::*)(P1) > struct op_mf {}; \
struct N##_helper {\
  typedef char small_type;\
  typedef class big_tag { char dummy[2];} big_type;\
  template<typename P>\
  static small_type test(op_mf<P, &P::D>*);\
  template<typename P>\
  static big_type test(...);\
}; \
} \
template<typename T>\
struct N\
{\
  typedef N##_detail::N##_helper helper; \
  enum { value = sizeof( helper::test<T>(0) ) == sizeof(helper::small_type) };\
};

#define FAS_HAS_MEMBER_FUNCTION2(N, D, R, P1, P2)\
namespace N##_detail{\
template < typename T, R (T::*)(P1, P2) > struct op_mf {}; \
struct N##_helper {\
  typedef char small_type;\
  typedef class big_tag { char dummy[2];} big_type;\
  template<typename P>\
  static small_type test(op_mf<P, &P::D>*);\
  template<typename P>\
  static big_type test(...);\
}; \
} \
template<typename T>\
struct N\
{\
  typedef N##_detail::N##_helper helper; \
  enum { value = sizeof( helper::test<T>(0) ) == sizeof(helper::small_type) };\
};

#define FAS_HAS_MEMBER_FUNCTION3(N, D, R, P1, P2, P3)\
namespace N##_detail{\
template < typename T, R (T::*)(P1, P2, P3) > struct op_mf {}; \
struct N##_helper {\
  typedef char small_type;\
  typedef class big_tag { char dummy[2];} big_type;\
  template<typename P>\
  static small_type test(op_mf<P, &P::D>*);\
  template<typename P>\
  static big_type test(...);\
}; \
} \
template<typename T>\
struct N\
{\
  typedef N##_detail::N##_helper helper; \
  enum { value = sizeof( helper::test<T>(0) ) == sizeof(helper::small_type) };\
};

#define FAS_HAS_MEMBER_FUNCTION4(N, D, R, P1, P2, P3, P4)\
namespace N##_detail{\
template < typename T, R (T::*)(P1, P2, P3, P4) > struct op_mf {}; \
struct N##_helper {\
  typedef char small_type;\
  typedef class big_tag { char dummy[2];} big_type;\
  template<typename P>\
  static small_type test(op_mf<P, &P::D>*);\
  template<typename P>\
  static big_type test(...);\
}; \
} \
template<typename T>\
struct N\
{\
  typedef N##_detail::N##_helper helper; \
  enum { value = sizeof( helper::test<T>(0) ) == sizeof(helper::small_type) };\
};

#define FAS_HAS_MEMBER_FUNCTION5(N, D, R, P1, P2, P3, P4, P5)\
namespace N##_detail{\
template < typename T, R (T::*)(P1, P2, P3, P4, P5) > struct op_mf {}; \
struct N##_helper {\
  typedef char small_type;\
  typedef class big_tag { char dummy[2];} big_type;\
  template<typename P>\
  static small_type test(op_mf<P, &P::D>*);\
  template<typename P>\
  static big_type test(...);\
}; \
} \
template<typename T>\
struct N\
{\
  typedef N##_detail::N##_helper helper; \
  enum { value = sizeof( helper::test<T>(0) ) == sizeof(helper::small_type) };\
};

#endif
