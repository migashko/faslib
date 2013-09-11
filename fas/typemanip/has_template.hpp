//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TYPEMANIP_HAS_TEMPLATE_HPP
#define FAS_TYPEMANIP_HAS_TEMPLATE_HPP

#define FAS_HAS_TEMPLATE0(N, D)\
namespace N##_detail{\
struct N##_helper {\
  typedef char small_type;\
  typedef struct big_tag { char dummy[2];} big_type;\
  template<typename P>\
  static small_type test(typename P::D const *);\
  template<typename P>\
  static big_type test(...);\
}; \
} \
template<typename T>\
struct N\
{\
  typedef N##_detail::N##_helper helper; \
  enum { \
    value = sizeof( helper::test<T>(0) ) == sizeof(helper::small_type) \
  };\
};

#define FAS_HAS_TEMPLATE1(N, D)\
namespace N##_detail{\
struct N##_helper {\
  typedef char small_type;\
  typedef struct big_tag { char dummy[2];} big_type;\
  template<typename P, typename P1>\
  static small_type test(typename P::template D<P1> const *);\
  template<typename P, typename P1>\
  static big_type test(...);\
}; \
} \
template<typename T>\
struct N\
{\
  typedef N##_detail::N##_helper helper; \
  enum { \
    value = sizeof( helper::test<T,void>(0) ) == sizeof(helper::small_type) \
  };\
};

#define FAS_HAS_TEMPLATE2(N, D)\
namespace N##_detail{\
struct N##_helper {\
  typedef char small_type;\
  typedef struct big_tag { char dummy[2];} big_type;\
  template<typename P, typename P1, typename P2>\
  static small_type test(typename P::template D<P1, P2> const *);\
  template<typename P, typename P1, typename P2>\
  static big_type test(...);\
}; \
} \
template<typename T>\
struct N\
{\
  typedef N##_detail::N##_helper helper; \
  enum { \
    value = sizeof( helper::test<T,void, void>(0) ) == sizeof(helper::small_type) \
  };\
};

#define FAS_HAS_TEMPLATE3(N, D)\
namespace N##_detail{\
struct N##_helper {\
  typedef char small_type;\
  typedef struct big_tag { char dummy[2];} big_type;\
  template<typename P, typename P1, typename P2, typename P3>\
  static small_type test(typename P::template D<P1, P2, P3> const *);\
  template<typename P, typename P1, typename P2, typename P3>\
  static big_type test(...);\
}; \
} \
template<typename T>\
struct N\
{\
  typedef N##_detail::N##_helper helper; \
  enum { \
    value = sizeof( helper::test<T,void, void, void>(0) ) == sizeof(helper::small_type) \
  };\
};

#define FAS_HAS_TEMPLATE4(N, D)\
namespace N##_detail{\
struct N##_helper {\
  typedef char small_type;\
  typedef struct big_tag { char dummy[2];} big_type;\
  template<typename P, typename P1, typename P2, typename P3, typename P4>\
  static small_type test(typename P::template D<P1, P2, P3, P4> const *);\
  template<typename P, typename P1, typename P2, typename P3, typename P4>\
  static big_type test(...);\
}; \
} \
template<typename T>\
struct N\
{\
  typedef N##_detail::N##_helper helper; \
  enum { \
    value = sizeof( helper::test<T,void, void, void, void>(0) ) == sizeof(helper::small_type) \
  };\
};

#define FAS_HAS_TEMPLATE5(N, D)\
namespace N##_detail{\
struct N##_helper {\
  typedef char small_type;\
  typedef struct big_tag { char dummy[2];} big_type;\
  template<typename P, typename P1, typename P2, typename P3, typename P4, typename P5>\
  static small_type test(typename P::template D<P1, P2, P3, P4, P5> const *);\
  template<typename P, typename P1, typename P2, typename P3, typename P4, typename P5>\
  static big_type test(...);\
}; \
} \
template<typename T>\
struct N\
{\
  typedef N##_detail::N##_helper helper; \
  enum { \
    value = sizeof( helper::test<T,void, void, void, void, void>(0) ) == sizeof(helper::small_type) \
  };\
};

#endif
