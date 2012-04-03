#include "basic_test.hpp"
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



UNIT(trivial, "trivial range testing")
{
  using namespace fas;
  int v1 = 1;
  typedef trivial_range<int*> range_type;
  typedef trivial_range<const int*> const_range_type;
  range_type r1(&v1);
  trivial_test(t, r1);
  trivial_const_test(t, const_range_type(&v1));
};

UNIT(input, "input range testing")
{
  using namespace fas;
  std::stringstream ss;
  ss << 1 << " " << 2;
  
  typedef std::istream_iterator<int> iterator;
  typedef input_range< iterator > range_type;
  range_type r1 = range_type( iterator(ss), iterator() );
  input_test(t, r1);

  /*
  make_ibufrange(ss);
  make_ibufrange(std::cin);
  make_irange(ss);
  make_irange(std::cin);

  make_obufrange(ss);
  make_obufrange(std::cout);
  make_orange(ss);
  make_orange(std::cout);
  */
}

UNIT(output1, "output range testing (back_insert_iterator)")
{
  using namespace fas;
  using namespace fas::testing;

  typedef std::vector< int> container_type;
  typedef std::back_insert_iterator< container_type > iterator;
  /*typedef iterator::iterator iterator2;
  static_check< has_iterator_category2<iterator>::value > test1;
  static_check< !has_iterator2<iterator2>::value > test2;
  static_check< !has_range_category2<iterator>::value > test3;
  */
  
  typedef typerange< iterator >::range range_type;
  
  container_type cnt1;
  
  iterator cnt1itr(cnt1);
  range_type r1 = /*make_init_*/range( iterator(cnt1) );
  output_test(t, r1);
  
  container_type cnt2;
  cnt2.push_back(1);
  cnt2.push_back(2);
  
  t << equal<expect>(cnt1, cnt2) << "cnt1 == cnt2";
  
};

UNIT(output2, "output range testing (front_insert_iterator)")
{
  using namespace fas;
  using namespace fas::testing;

  typedef std::list<int> container_type;
  typedef std::front_insert_iterator< container_type > iterator;
  typedef output_range< iterator > range_type;
  
  container_type cnt1;
  
  range_type r1 = range_type( iterator(cnt1) );
  output_test(t, r1);
  
  container_type cnt2;
  cnt2.push_front(1);
  cnt2.push_front(2);
  
  t << equal<expect>(cnt1, cnt2) << "cnt1 == cnt2";
};


UNIT(output3, "output range testing (output_iterator)")
{
  using namespace fas;
  using namespace fas::testing;

  std::stringstream ss;
  typedef std::ostream_iterator< int > iterator;
  typedef output_range< iterator > range_type;
  range_type r1 = range_type( iterator(ss, " ") );
  output_test(t, r1);
  t << equal<expect>( std::string("1 2 "), ss.str() ) << "ss.str() == \"1 2\" [[" << ss.str() << "]]";
};

UNIT(forward, "forward range testing")
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
};

UNIT(forward_const, "forward_const range testing")
{
  using namespace fas;
  using namespace fas::testing;
  int cnt[]={1,2};

  typedef forward_range<const int*> range_type;
  range_type r1(cnt, cnt + sizeof(cnt)/sizeof(int));
  trivial_const_test(t, r1);
  forward_test(t, r1);

  /*t << equal<expect> ( 1, *(r1++) ) << FAS_TESTING_FILE_LINE;
  t << equal<expect> ( 2, *(r1++) ) << FAS_TESTING_FILE_LINE;
  */
};

UNIT(bidirectional, "bidirectional range testing")
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
  //range_type r1(cnt.begin(), cnt.end());
  trivial_test(t, r1);
  input_test(t, r1);
  output_test(t, r1);
  forward_test(t, r1);
  bidirectional_test(t, r1);
};

UNIT(random_access, "random access range testing")
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
};

UNIT(random_access_const, "random access range testing")
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
  t << is_true<expect>( r1[1] == 2 ) << "itr[1] == 2 " << itr[1];
  random_access_const_test(t, r1);
};


UNIT(initial_range_sequence, "initial sequence range testing")
{
  using namespace fas;
  using namespace fas::testing;
  typedef std::vector<int> container_type;
  
  typedef typename typerange<container_type>::init_range/*initial_range_type*/ range_type;
  /*enum { is_s =  range_traits<container_type>::is_sequence_container };
  enum { is_a =  range_traits<container_type>::is_associative_container };
  enum { result = static_check<is_s>::value + static_check<!is_a>::value };
  */
  container_type cnt;
  range_type r = init_range(  cnt );
  *(r++) = 1;
  *(r) = 2;
  *(r) = 3;
  t << equal<assert>( cnt.size(), (size_t)3 ) << "cnt.size()!=3";
  t << equal<expect>( cnt[0], 1 ) << "cnt[0]!=1";
  t << equal<expect>( cnt[1], 2 ) << "cnt[1]!=2";
  t << equal<expect>( cnt[2], 3 ) << "cnt[2]!=3";
}

UNIT(initial_range_associative, "initial associative range testing")
{
  using namespace fas;
  using namespace fas::testing;
  typedef std::set<int> container_type;
  
  typedef typename typerange<container_type>::init_range range_type;
  /*enum { is_s =  range_traits<container_type>::is_sequence_container };
  enum { is_a =  range_traits<container_type>::is_associative_container };
  enum { result = static_check<!is_s>::value + static_check<is_a>::value };*/
  container_type cnt;
  range_type r = init_range(  cnt );
  *(r) = 3;
  *(r++) = 2;
  *(r) = 1;
  container_type::iterator itr = cnt.begin();
  t << equal<assert>( cnt.size(), (size_t)3 ) << "cnt.size()!=3";
  t << equal<expect>( *(itr++), 1 ) << "cnt[0]!=1";
  t << equal<expect>( *(itr++), 2 ) << "cnt[1]!=2";
  t << equal<expect>( *(itr++), 3 ) << "cnt[2]!=3";
}

BEGIN_SUITE(basic_range_suite, "basic range suite")
  ADD_UNIT(trivial)
  ADD_UNIT(input)
  //ADD_UNIT(input2)
  ADD_UNIT(output1)
  ADD_UNIT(output2)
  ADD_UNIT(output3)
  ADD_UNIT(forward)
  ADD_UNIT(forward_const)
  ADD_UNIT(bidirectional)
  ADD_UNIT(random_access)
  ADD_UNIT(random_access_const)
  ADD_UNIT(initial_range_sequence)
  ADD_UNIT(initial_range_associative)
  
  //ADD_CLASS(test_data)
END_SUITE(basic_range_suite)
