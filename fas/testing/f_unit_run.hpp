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
  f_unit_run()
    : fail_flag(false)
  {}
  
  template<typename T, typename Tg>
  void operator()(T& t, tag<Tg> )
  {
    typename T::aspect::template advice_cast<Tg>::type &u = t.get_aspect().template get<Tg>();

    if ( fail_flag )
    {
      t.out() << std::endl << SKIP << u.fas_name();
      t.unit_skip(u);
      return;
    }
      
    
    t.out() << std::endl << RUN << u.fas_name();
    t.unit_begin(u);
    try
    {
      u(t);
    }
    catch(const fail_error& )
    {
      // Прерван текущий юнит. Ничего не делаем 
    }
    catch(const fatal_error& )
    {
      // Прерван suit. Остальные юниты пропускаем, но по текущему выводим инфу
      fail_flag = true;
    }    
    
    t.unit_end(u);

    if (t.current_unit_ok())
      t.out() << std::endl << OK;
    else
      this->print_fail(t, u);
  }

  template<typename T, typename U>
  static void print_fail(T& t, U& u)
  {
    t.out() << std::endl << UNIT_FAIL << u.fas_name();
    if ( !u.fas_desc().empty() )
      t.out() << ". " << u.fas_desc();
    const unit_counts& counts = t.current_unit_counts();
    t.out() << std::endl << UNIT_FAIL << "statements: " << counts.statements;
    if ( counts.errors!=0)
      t.out() << std::endl << UNIT_FAIL << ::fas::console::light_red << "errors: " << counts.errors << ::fas::console::restore_colors;
    if ( counts.fails!=0)
      t.out() << std::endl << UNIT_FAIL << ::fas::console::light_red << "fails: " << counts.fails << ::fas::console::restore_colors;
    if ( counts.fatals!=0)
      t.out() << std::endl << UNIT_FAIL << ::fas::console::light_red << "fatals: " << counts.fatals << ::fas::console::restore_colors;
  }
private:
  bool fail_flag;
};

}}

#endif
