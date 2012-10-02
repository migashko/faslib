//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#include <fas/testing/suite.hpp>
#include <fas/testing/statements.hpp>
#include <fas/static_check/static_check.hpp>
#include <sstream>
#include <iostream>

using namespace fas;
using namespace fas::testing;

bool test_expect_out1()
{
  std::stringstream ss;
  suite<> su(ss);
  su << is_true<expect>( 1 < 2 ) << "Test message.";
  std::cout << su.stub().str() << std::endl;
  if ( !ss.str().empty() ) return false;
  if ( su.stub().str() != "Test message." ) return false;
  return true;
}

bool test_expect_out2()
{
  std::stringstream ss;
  suite<> su(ss);
  su << is_true<expect>( 2 < 1 ) << "Test message.";
  std::cout << ss.str() << std::endl;
  if ( !su.stub().str().empty() ) return false;
  if ( ss.str() != "\n[   ERROR ] Is true statement. Test message." ) return false;
  return true;
}

bool test_assert_out1()
{
  std::stringstream ss;
  suite<> su(ss);
  su << is_true<expect>( 1 < 2 ) << "Test message.";
  if ( !ss.str().empty() ) return false;
  if ( su.stub().str() != "Test message." ) return false;
  return true;
}

bool test_assert_out2()
{
  std::stringstream ss;
  suite<> su(ss);
  su << is_true<assert>( 2 < 1 ) << "Test message.";
  std::cout << ss.str() << std::endl;
  if ( !su.stub().str().empty() ) return false;
  if ( ss.str() != "\n[    FAIL ] Is true statement. Test message." ) return false;
  return true;
}

bool test_critical_out1()
{
  std::stringstream ss;
  suite<> su(ss);
  su << is_true<critical>( 1 < 2 ) << "Test message.";
  if ( !ss.str().empty() ) return false;
  if ( su.stub().str() != "Test message." ) return false;
  return true;
}

bool test_critical_out2()
{
  std::stringstream ss;
  suite<> su(ss);
  su << is_true<critical>( 2 < 1 ) << "Test message.";
  std::cout << ss.str() << std::endl;
  if ( !su.stub().str().empty() ) return false;
  if ( ss.str() != "\n[   FATAL ] Is true statement. Test message." ) return false;
  return true;
}

bool test_message_out()
{
  std::stringstream ss;
  suite<> su(ss);
  su << message("Message1. ") << "Message2. " << "Message3.";
  std::cout << ss.str() << std::endl;
  if ( !su.stub().str().empty() ) return false;
  if ( ss.str() != "\n[ MESSAGE ] Message1. Message2. Message3." ) return false;
  return true;
}

bool test_warning_out()
{
  std::stringstream ss;
  suite<> su(ss);
  su << warning("Message1. ") << "Message2.";
  std::cout << ss.str() << std::endl;
  if ( !su.stub().str().empty() ) return false;
  if ( ss.str() != "\n[ WARNING ] Message1. Message2." ) return false;
  return true;
}

bool test_error_out()
{
  std::stringstream ss;
  suite<> su(ss);
  su << error("Message1. ") << "Message2.";
  std::cout << ss.str() << std::endl;
  std::cout << "stub:" << su.stub().str() << "|" << std::endl;
  if ( !su.stub().str().empty() ) return false;
  if ( ss.str() != "\n[   ERROR ] Message1. Message2." ) return false;
  return true;
}

bool test_fatal_out()
{
  std::stringstream ss;
  suite<> su(ss);
  su << fatal("Message1. ") << "Message2.";
  std::cout << ss.str() << std::endl;
  std::cout << "stub:" << su.stub().str() << "|" << std::endl;
  if ( !su.stub().str().empty() ) return false;
  if ( ss.str() != "\n[   FATAL ] Message1. Message2." ) return false;
  return true;
}

int main()
{
  if (!test_expect_out1()) return -1;
  if (!test_expect_out2()) return -1;
  if (!test_assert_out1()) return -1;
  if (!test_assert_out2()) return -1;
  if (!test_critical_out1()) return -1;
  if (!test_critical_out2()) return -1;
  if (!test_message_out()) return -1;
  if (!test_warning_out()) return -1;
  if (!test_error_out()) return -1;
  if (!test_fatal_out()) return -1;
  std::cout << "OK" << std::endl;
  return 0;
}
