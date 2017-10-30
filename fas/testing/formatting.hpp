//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TESTING_FORMATTING_HPP
#define FAS_TESTING_FORMATTING_HPP

#include <fas/system/colorized.hpp>
#include <fas/testing/tags.hpp>

namespace fas{ namespace testing{

inline void PASSED(_passed_) {}
inline void RED_PASSED(_red_passed_) {}
inline void OK(_ok_) {}
inline void FAIL(_fail_) {}
inline void EXCEPT(_except_) {}
inline void FATAL(_fatal_) {}
inline void CRASH(_crash_) {}
inline void RUN(_run_) {}
inline void SKIP(_skip_) {}
inline void WARNING(_warning_) {}
inline void MESSAGE(_message_) {}
inline void ERROR_MESSAGE(_error_) {}

inline void SUITE_BEG(_suite_beg_) {}
inline void SUITE_END(_suite_end_) {}

inline void UNIT_FAIL(_unit_fail_res_){}
inline void SUITE_FAIL(_suite_fail_res_){}
inline void TEST_FAIL(_test_fail_res_){}

inline void stop(_stop_){}
inline void nothing(_nothing_){}
inline void flush(_flush_){}

}}

namespace std
{

  inline ostream& operator<<(ostream& os, void (*)( ::fas::testing::_passed_) )
  {
    return os << ::fas::console::green << "[ PASSED  ] " << fas::console::restore_colors;
  }

  inline ostream& operator<<(ostream& os, void (*)( ::fas::testing::_ok_) )
  {
    return os << ::fas::console::green << "[      OK ] " << fas::console::restore_colors;
  }

  inline ostream& operator<<(ostream& os, void (*)( ::fas::testing::_skip_) )
  {
    return os << ::fas::console::magenta << "[    SKIP ] " << fas::console::restore_colors;
  }

  inline ostream& operator<<(ostream& os, void (*)( ::fas::testing::_run_) )
  {
    return os << ::fas::console::green << "[ RUN     ] " << fas::console::restore_colors;
  }

  inline ostream& operator<<(ostream& os, void (*)( ::fas::testing::_red_passed_) )
  {
    return os << ::fas::console::light_red << "[ PASSED  ] " << fas::console::restore_colors;
  }

    inline ostream& operator<<(ostream& os, void (*)( ::fas::testing::_fail_) )
  {
    return os << ::fas::console::light_red << "[    FAIL ] " << fas::console::restore_colors;
  }

  inline ostream& operator<<(ostream& os, void (*)( ::fas::testing::_except_) )
  {
    return os << ::fas::console::light_red << "[  EXCEPT ] " << fas::console::restore_colors;
  }

  inline ostream& operator<<(ostream& os, void (*)(::fas::testing::_fatal_) )
  {
    return os << ::fas::console::red << "[   FATAL ] " << fas::console::restore_colors;
  }

  inline ostream& operator<<(ostream& os, void (*)(::fas::testing::_crash_) )
  {
    return os << ::fas::console::brown << "[   CRASH ] " << fas::console::restore_colors;
  }

  inline ostream& operator<<(ostream& os, void (*)(::fas::testing::_warning_) )
  {
    return os << ::fas::console::yellow <<"[ WARNING ] " << fas::console::restore_colors;
  }

  inline ostream& operator<<(ostream& os, void (*)(::fas::testing::_message_) )
  {
    return os << ::fas::console::blue <<"[ MESSAGE ] " << fas::console::restore_colors;
  }

  inline ostream& operator<<(ostream& os, void (*)(::fas::testing::_error_) )
  {
    return os << ::fas::console::light_red << "[   ERROR ] " << fas::console::restore_colors;
  }

  inline ostream& operator<<(ostream& os, void (*)(::fas::testing::_suite_beg_) )
  {
    return os << ::fas::console::cyan << "[ --BEG-- ] " << fas::console::restore_colors;
  }

  inline ostream& operator<<(ostream& os, void (*)(::fas::testing::_suite_end_) )
  {
    return os << ::fas::console::cyan << "[ --END-- ] " << fas::console::restore_colors;
  }

  inline ostream& operator<<(ostream& os, void (*)(::fas::testing::_unit_fail_res_) )
  {
    return os << ::fas::console::red <<  "[ ------- ] " << fas::console::restore_colors;
  }

  inline ostream& operator<<(ostream& os, void (*)(::fas::testing::_suite_fail_res_))
  {
    return os << ::fas::console::red << "[ ======= ] " << fas::console::restore_colors;
  }

  inline ostream& operator<<(ostream& os, void (*)(::fas::testing::_test_fail_res_))
  {
    return os << ::fas::console::red << "[ ******* ] " << fas::console::restore_colors;
  }

  inline ostream& operator<<(ostream& os, void (*)(::fas::testing::_stop_) )
  {
    return os << std::endl << ::fas::console::red << "STOP" << fas::console::restore_colors << " Improper use of stop. Usage: 't << stop;'" << std::endl;
  }

  inline ostream& operator<<(ostream& os, void (*)(::fas::testing::_nothing_) )
  {
    return os << std::endl << ::fas::console::red << "NOTHING" << fas::console::restore_colors << " Improper use of 'nothing'. Usage: 't << nothing;'" << std::endl;
  }

  inline ostream& operator<<(ostream& os, void (*)(::fas::testing::_flush_) )
  {
    os.flush();
    return os;
  }

}

#endif
