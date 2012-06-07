//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#include <fas/testing/statements.hpp>
#include <fas/static_check/static_check.hpp>
#include <iostream>

using namespace fas;
using namespace fas::testing;

int main()
{
  statement<expect> statement_expect(true);
  statement<assert> statement_assert(false);
  statement<critical> statement_critical(true);

  equal<critical> equal_critical(1, 2);
  if ( equal_critical.result )
    return -1;

  equal_str<expect> equal_str_expect("ура", "ура");
  if ( !equal_str_expect.result )
    return -1;

  is_true<> is_true_assert(true);
  if ( !is_true_assert.result )
    return -1;

  is_false<> is_false_assert(true);
  if ( is_false_assert.result )
    return -1;

  message msg("test message");
  if ( !msg.result || msg.text!="test message")
    return -1;

  warning wrn("test warning");
  if ( wrn.result || wrn.text!="test warning")
    return -1;

  error err("test error");
  if ( err.result || err.text!="test error")
    return -1;

  fatal ftl("test fatal");
  if ( ftl.result || ftl.text!="test fatal")
    return -1;

  std::cout << "OK" << std::endl;
  return 0;
};

