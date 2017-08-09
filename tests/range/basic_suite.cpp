//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//


#include "basic_suite.hpp"
#include <fas/testing.hpp>
#include <fas/range.hpp>
#include <fas/static_check/static_check.hpp>

#include <vector>
#include <set>
#include <list>
#include <iterator>
#include <sstream>
#include <iostream>

struct test_data
  : std::vector<int>
{
  test_data()
  {
    this->push_back(1);
    this->push_back(2);
  }
};



UNIT(trivial_unit, "")
{
  //t.get_aspect().template get<int>();
  using namespace fas;
  int v1 = 1;
  typedef trivial_range<int*> range_type;
  typedef trivial_range<const int*> const_range_type;
  range_type r1(&v1);
  trivial_test(t, r1);
  trivial_const_test(t, const_range_type(&v1));
}

UNIT(input_unit, "")
{
  using namespace fas;
  std::stringstream ss;
  ss << 1 << " " << 2;

  typedef std::istream_iterator<int> iterator;
  typedef input_range< iterator, int> range_type;
  range_type r1 = range_type( iterator(ss), iterator() );
  input_test(t, r1);
}

UNIT(output1_unit, "")
{
  using namespace fas;
  using namespace fas::testing;

  typedef std::vector< int> container_type;
  typedef std::back_insert_iterator< container_type > iterator;

  typedef typerange< iterator >::range range_type;

  container_type cnt1;

  //iterator cnt1itr(cnt1);
  range_type r1 = range( iterator(cnt1) );
  output_test(t, r1);

  container_type cnt2;
  cnt2.push_back(1);
  cnt2.push_back(2);

  t << equal<expect>(cnt1, cnt2) << FAS_TESTING_FILE_LINE;

}

UNIT(output2_unit, "")
{
  using namespace fas;
  using namespace fas::testing;

  typedef std::list<int> container_type;
  typedef std::front_insert_iterator< container_type > iterator;
  typedef output_range< iterator, int> range_type;

  container_type cnt1;

  range_type r1 = range_type( iterator(cnt1) );
  output_test(t, r1);

  container_type cnt2;
  cnt2.push_front(1);
  cnt2.push_front(2);

  t << equal<expect>(cnt1, cnt2) << FAS_TESTING_FILE_LINE;
}


UNIT(output3_unit, "")
{
  using namespace fas;
  using namespace fas::testing;

  std::stringstream ss;
  typedef std::ostream_iterator< int > iterator;
  typedef output_range< iterator, int> range_type;
  range_type r1 = range_type( iterator(ss, " ") );
  output_test(t, r1);
  t << equal<expect>( std::string("1 2 "), ss.str() ) << FAS_TESTING_FILE_LINE;
}

UNIT(forward_unit, "")
{
  using namespace fas;
  using namespace fas::testing;
  int cnt[]={1,2};

  typedef forward_range<int*> range_type;
  range_type r1(cnt, cnt + sizeof(cnt)/sizeof(int));
  trivial_test(t, r1);
  input_test(t, r1);
  output_test(t, r1);
  forward_test(t, r1);
}

UNIT(forward_const_unit, "")
{
  using namespace fas;
  using namespace fas::testing;
  int cnt[]={1,2};

  typedef forward_range<const int*> range_type;
  range_type r1(cnt, cnt + sizeof(cnt)/sizeof(int));
  trivial_const_test(t, r1);
  forward_test(t, r1);
}

UNIT(bidirectional_unit, "")
{
  using namespace fas;
  using namespace fas::testing;
  typedef std::list<int> container_type;
  typedef container_type::iterator iterator;
  typedef bidirectional_range<iterator> range_type;

  container_type cnt;
  cnt.push_back(1);
  cnt.push_back(2);
  iterator itr1 = cnt.begin();
  iterator itr2=cnt.end();
  range_type r1(itr1, itr2);
  trivial_test(t, r1);
  input_test(t, r1);
  output_test(t, r1);
  forward_test(t, r1);
  bidirectional_test(t, r1);
}

UNIT(random_access_unit, "")
{
  using namespace fas;
  using namespace fas::testing;
  typedef std::vector<int> container_type;
  typedef container_type::iterator iterator;
  typedef random_access_range<iterator> range_type;

  container_type cnt;
  cnt.push_back(1);
  cnt.push_back(2);
  range_type r1(cnt.begin(), cnt.end());

  trivial_test(t, r1);
  input_test(t, r1);
  output_test(t, r1);
  forward_test(t, r1);
  bidirectional_test(t, r1);
  random_access_test(t, r1);
}

UNIT(random_access_const_unit, "")
{
  using namespace fas;
  using namespace fas::testing;
  typedef std::vector<int> container_type;
  typedef container_type::const_iterator iterator;
  typedef random_access_range<iterator> range_type;

  container_type cnt;
  cnt.push_back(1);
  cnt.push_back(2);
  range_type r1(cnt.begin(), cnt.end());

  trivial_const_test(t, r1);
  input_test(t, r1);
  //output_test(t, r1);
  forward_test(t, r1);
  bidirectional_test(t, r1);

  iterator itr = cnt.begin();
  t << is_true<expect>( itr[1] == 2 ) << FAS_TESTING_FILE_LINE;
  random_access_const_test(t, r1);
}


UNIT(initial_range_sequence_unit, "")
{
  using namespace fas;
  using namespace fas::testing;
  typedef std::vector<int> container_type;

  typedef typename typerange<container_type>::orange range_type;

  container_type cnt;
  range_type r = orange(  cnt );
  *(r++) = 1;
  *(r) = 2;
  *(r) = 3;
  t << equal<assert, size_t>( cnt.size(), 3 ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>( cnt[0], 1 ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>( cnt[1], 2 ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>( cnt[2], 3 ) << FAS_TESTING_FILE_LINE;
}

UNIT(initial_range_associative_unit, "")
{
  using namespace fas;
  using namespace fas::testing;
  typedef std::set<int> container_type;

  typedef typename typerange<container_type>::orange range_type;
  container_type cnt;
  range_type r = orange(  cnt );
  *(r) = 3;
  *(r++) = 2;
  *(r) = 1;
  container_type::iterator itr = cnt.begin();
  t << equal<assert>( cnt.size(), static_cast<size_t>(3) ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>( *(itr++), 1 ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>( *(itr++), 2 ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>( *(itr++), 3 ) << FAS_TESTING_FILE_LINE;
}

BEGIN_SUITE(basic_range_suite, "")
  ADD_UNIT(trivial_unit)
  ADD_UNIT(input_unit)
  ADD_UNIT(output1_unit)
  ADD_UNIT(output2_unit)
  ADD_UNIT(output3_unit)
  ADD_UNIT(forward_unit)
  ADD_UNIT(forward_const_unit)
  ADD_UNIT(bidirectional_unit)
  ADD_UNIT(random_access_unit)
  ADD_UNIT(random_access_const_unit)
  ADD_UNIT(initial_range_sequence_unit)
  ADD_UNIT(initial_range_associative_unit)
END_SUITE(basic_range_suite)
