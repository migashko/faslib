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

    t.out() << std::endl << RUN << u.fas_name();
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
      t.out() << std::endl << EXCEPT << e.what() << std::endl;
      this->print_fail(t, u);
      throw;
    }
    catch(...)
    {
      t.unit_end(u);
      t.out() << std::endl << EXCEPT << "Unhandled exception." << std::endl;
      this->print_fail(t, u);
      throw;
    }

    if (u.fas_ready())
      t.out() << std::endl << OK;
    else
      this->print_fail(t, u);
  }

  template<typename T, typename U>
  void print_fail(T& t, U& u)
  {
    t.out() << std::endl << UNIT_FAIL << u.fas_name();
    if ( !u.fas_desc().empty() )
      t.out() << "." << u.fas_desc();
    t.out() << std::endl << UNIT_FAIL << "statements: " << u.fas_counts().statements;
    if ( u.fas_counts().errors!=0)
      t.out() << std::endl << UNIT_FAIL << ::fas::console::light_red << "errors: " << u.fas_counts().errors << ::fas::console::restore_colors;
    if ( u.fas_counts().fails!=0)
      t.out() << std::endl << UNIT_FAIL << ::fas::console::light_red << "fails: " << u.fas_counts().fails << ::fas::console::restore_colors;
    if ( u.fas_counts().fatals!=0)
      t.out() << std::endl << UNIT_FAIL << ::fas::console::light_red << "fatals: " << u.fas_counts().fatals << ::fas::console::restore_colors;
  }
};

}}

#endif
