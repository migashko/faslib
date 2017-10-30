//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2012
//
// Copyright: See COPYING file that comes with this distribution
//

#include <fas/type_list.hpp>
#include <fas/aop.hpp>
#include <fas/aop/call_group.hpp>
#include <fas/mp.hpp>
#include <fas/typemanip.hpp>
#include <fas/static_check/static_check.hpp>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <iostream>

std::vector<int> test_values;

template<int P>
struct ad_test
{
  template<typename T>
  void operator()( T& ) const
  {
    test_values.push_back(P);
  }
};


struct _group1_;
struct _group2_;
struct _tag1_;
struct _tag2_;
struct _tag3_;
struct _tag4_;
struct _tag5_;

struct test_aspect: fas::aspect< fas::type_list_n<
  fas::advice<_tag1_, ad_test<1> >,
  fas::advice<_tag2_, ad_test<2> >,
  fas::advice<_tag3_, ad_test<3> >,
  fas::advice<_tag4_, ad_test<4> >,
  fas::advice<_tag5_, ad_test<5> >,
  fas::group<_group1_, fas::type_list_n<_tag1_, _tag2_, _tag3_>::type >,
  fas::group<_group2_, fas::type_list_n<_tag4_, _tag5_>::type >
>::type>{};

void show(const std::vector<int>& f, const std::vector<int>& s );
void show(const std::vector<int>& f, const std::vector<int>& s )
{
  std::cout << f.size() << " " << s.size() << std::endl;

  typedef std::vector<int>::const_iterator const_iterator;
  const_iterator fbeg = f.begin();
  const_iterator fend = f.end();
  const_iterator sbeg = s.begin();
  const_iterator send = s.end();

  for(;fbeg!=fend && sbeg!=send; ++fbeg, ++sbeg)
  {
    std::cout << *fbeg << "==" << *sbeg << std::endl;
  }
}

int main()
{
  std::vector<int> check_values;
  fas::aspect_class<test_aspect> test;

  test_values.clear();
  check_values.clear();
  for (int i=1; i < 4; ++i ) check_values.push_back(i);
  fas::call_group<_group1_>( test );
  if (test_values!=check_values)
  {
    show(test_values, check_values);
    return 1;
  }

  test_values.clear();
  check_values.clear();
  for (int i=1; i < 6; ++i ) check_values.push_back(i);
  for (int i=1; i < 4; ++i ) check_values.push_back(i);
  check_values.push_back(1);
  fas::call_group< fas::type_list_n<_group1_, _group2_, _group1_, _tag1_>::type >( test );
  if (test_values!=check_values)
  {
    show(test_values, check_values);
    return 1;
  }


  return 0;
}
