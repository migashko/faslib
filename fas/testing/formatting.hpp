#ifndef FAS_TESTING_FORMATTING_HPP
#define FAS_TESTING_FORMATTING_HPP

#include <fas/system/colorized.hpp>
#include <fas/testing/tags.hpp>



namespace fas{ namespace testing{



inline void PASSED(_passed_) {};
inline void OK(_ok_) {};
inline void FAIL(_fail_) {};
inline void EXCEPT(_except_) {};
inline void FATAL(_fatal_) {};
inline void RUN(_run_) {};
inline void WARNING(_warning_) {};
inline void MESSAGE(_message_) {};
inline void ERROR_MESSAGE(_error_) {};

inline void SUITE_BEG(_suite_beg_) {};
inline void SUITE_END(_suite_end_) {};

inline void UNIT_FAIL(_unit_fail_res_){};
inline void SUITE_FAIL(_suite_fail_res_){};
inline void TEST_FAIL(_test_fail_res_){};



}}

namespace std
{

  inline ostream& operator<<(ostream& o, void (*)( ::fas::testing::_passed_) )
  {
    return o << ::fas::green << "[ PASSED  ] " << fas::restore;
  }

  
  inline ostream& operator<<(ostream& o, void (*)( ::fas::testing::_ok_) )
  {
    return o << ::fas::green << "[      OK ] " << fas::restore;
  }

  inline ostream& operator<<(ostream& o, void (*)( ::fas::testing::_run_) )
  {
    return o << ::fas::green << "[ RUN     ] " << fas::restore;
  }

  
  inline ostream& operator<<(ostream& o, void (*)( ::fas::testing::_fail_) )
  {
    return o << ::fas::light_red << "[    FAIL ] " << fas::restore;
  }

  inline ostream& operator<<(ostream& o, void (*)( ::fas::testing::_except_) )
  {
    return o << ::fas::light_red << "[  EXCEPT ] " << fas::restore;
  }

  
  inline ostream& operator<<(ostream& o, void (*)(::fas::testing::_fatal_) )
  {
    return o << ::fas::red << "[   FATAL ] " << fas::restore;
  }

  
  inline ostream& operator<<(ostream& o, void (*)(::fas::testing::_warning_) )
  {
    return o << ::fas::yellow <<"[ WARNING ] " << fas::restore;
  }

  inline ostream& operator<<(ostream& o, void (*)(::fas::testing::_message_) )
  {
    return o << ::fas::blue <<"[ MESSAGE ] " << fas::restore;
  }

  inline ostream& operator<<(ostream& o, void (*)(::fas::testing::_error_) )
  {
    return o << ::fas::light_red << "[   ERROR ] " << fas::restore;
  }

  inline ostream& operator<<(ostream& o, void (*)(::fas::testing::_suite_beg_) )
  {
    return o << ::fas::cyan << "[ --BEG-- ] " << fas::restore;
  }

  inline ostream& operator<<(ostream& o, void (*)(::fas::testing::_suite_end_) )
  {
    return o << ::fas::cyan << "[ --END-- ] " << fas::restore;
  }
  
  inline ostream& operator<<(ostream& o, void (*)(::fas::testing::_unit_fail_res_) )
  {
    return o << ::fas::red <<  "[ ------- ] " << fas::restore;
  };
  
  inline ostream& operator<<(ostream& o, void (*)(::fas::testing::_suite_fail_res_))
  {
    return o << ::fas::red << "[ ======= ] " << fas::restore;
  };
  
  inline ostream& operator<<(ostream& o, void (*)(::fas::testing::_test_fail_res_))
  {
    return o << ::fas::red << "[ ******* ] " << fas::restore;
  }

  inline ostream& operator<<(ostream& o, void (*)(::fas::testing::_stop_) )
  {
    return o << std::endl << ::fas::red << "STOP" << fas::restore << " error: use t << stop" << std::endl;
  }

}

#endif
