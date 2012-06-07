//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TESTING_F_UNIT_RUN_HPP
#define FAS_TESTING_F_UNIT_RUN_HPP

#include <fas/testing/formatting.hpp>
#include <fas/testing/exceptions.hpp>
#include <fas/aop/tag.hpp>
#include <sstream>
#include <iostream>

namespace fas{ namespace testing{

struct f_unit_run
{
  template<typename T, typename Tg>
  void operator()(T& t, tag<Tg> )
  {
    typename T::aspect::template advice_cast<Tg>::type &u = t.get_aspect().template get<Tg>();
    
    t.out() << std::endl << RUN << u.name();
    try
    {
      t.unit_begin(u);
      u(t);
      t.unit_end(u);
    }
    catch(const fail_error& )
    {
      t.unit_end(u);
    }
    catch(const fatal_error&)
    {
      t.unit_end(u);
      this->print_fail(t, u);
      throw;
    }
    catch(const std::exception& e)
    {
      t.unit_end(u);
      t.out() << EXCEPT << e.what() << std::endl;
      this->print_fail(t, u);
      throw;
    }
    catch(...)
    {
      t.unit_end(u);
      t.out() << EXCEPT << "Unhandled exception." << std::endl;
      this->print_fail(t, u);
      throw;
    }
    
    if (u)
      t.out() << std::endl << OK;
    else
      this->print_fail(t, u);
  }

  template<typename T, typename U>
  void print_fail(T& t, U& u)
  {
    t.out() << std::endl << UNIT_FAIL << u.name();
    if ( !u.desc().empty() )
      t.out() << "." << u.desc();
    t.out() << std::endl << UNIT_FAIL << "statements: " << u.counts().statements;
    if ( u.counts().errors!=0)
      t.out() << std::endl << UNIT_FAIL << light_red << "errors: " << u.counts().errors << restore;
    if ( u.counts().fails!=0)
      t.out() << std::endl << UNIT_FAIL << light_red << "fails: " << u.counts().fails << restore;
    if ( u.counts().fatals!=0)
      t.out() << std::endl << UNIT_FAIL << light_red << "fatals: " << u.counts().fatals << restore;
  }
};

}}

#endif
