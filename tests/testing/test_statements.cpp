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
  
  double d1=0.0, d2=0.0;
  int    i1=0;
  
  if ( equal<expect, double>(i1, d1).result != true )
    return -1;

  if ( equal<expect, double>(d2, d1, "test").result != true )
    return -1;

  if ( equal<expect, size_t>(i1, d1).result != true )
    return -1;

  if ( equal<expect, size_t>(d2, d1, "test").result != true )
    return -1;
  
  if ( less_equal<expect, double>(i1, d1).result != true )
    return -1;

  if ( less_equal<expect, double>(d2, d1, "test").result != true )
    return -1;

  if ( less_equal<expect, size_t>(i1, d1).result != true )
    return -1;

  if ( less_equal<expect, size_t>(d2, d1, "test").result != true )
    return -1;
  
  if ( greater_equal<expect, double>(i1, d1).result != true )
    return -1;

  if ( greater_equal<expect, double>(d2, d1, "test").result != true )
    return -1;

  if ( greater_equal<expect, size_t>(i1, d1).result != true )
    return -1;

  if ( greater_equal<expect, size_t>(d2, d1, "test").result != true )
    return -1;
  
  if ( less<expect, double>(i1, d1).result != false )
    return -1;

  if ( less<expect, double>(d2, d1, "test").result != false )
    return -1;

  if ( less<expect, size_t>(i1, d1).result != false )
    return -1;

  if ( less<expect, size_t>(d2, d1, "test").result != false)
    return -1;
  
  if ( greater<expect, double>(i1, d1).result != false )
    return -1;

  if ( greater<expect, double>(d2, d1, "test").result != false )
    return -1;

  if ( greater<expect, size_t>(i1, d1).result != false )
    return -1;

  if ( greater<expect, size_t>(d2, d1, "test").result != false )
    return -1;
    
  
  std::cout << "OK" << std::endl;
  return 0;
}

