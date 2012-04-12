#include <fas/testing/statements.hpp>
#include <fas/range.hpp>

// &(*r1) + 1 == &(*r2) *r1 == 1 *r2==2

template<typename R, typename T>
inline void trivial_test(T& t, R r1)
{
  using namespace ::fas::testing;

  typedef typename R::iterator_category iterator_category;
  typedef typename R::value_type        value_type;
  typedef typename R::difference_type   difference_type;
  typedef typename R::pointer           pointer;
  typedef typename R::reference         reference;

  t << equal<expect>( *r1, 1 ) << FAS_TESTING_FILE_LINE;
  *r1 = 2;
  t << equal<expect>( *r1, 2 ) << FAS_TESTING_FILE_LINE;
  t << equal<assert>( r1.operator ->(), &(*r1) ) << FAS_TESTING_FILE_LINE << stop;
  *(r1.operator ->() ) = 3;
  t << equal<expect>( *r1, 3 ) << FAS_TESTING_FILE_LINE;
  *r1 = 1;
  
  R r_tmp = r1;
  t << equal<expect>( r1, r_tmp ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>( &(*r1), &(*r_tmp) ) << FAS_TESTING_FILE_LINE;
}

template<typename R, typename T>
inline void trivial_const_test(T& t, R r1)
{
  using namespace ::fas::testing;
  t << equal<expect>( *r1, 1 ) << FAS_TESTING_FILE_LINE;
  R r_tmp = r1;
  t << equal<expect>( r1, r_tmp ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>( &(*r1), &(*r_tmp) ) << FAS_TESTING_FILE_LINE;
}

template<typename R, typename T>
inline void input_test(T& t, R r1)
{
  using namespace ::fas::testing;
  
  t << is_true<expect>( r1 ) << FAS_TESTING_FILE_LINE;
  t << is_true<expect>( *r1 == 1 ) << FAS_TESTING_FILE_LINE;
  ++r1;
  t << is_true<expect>( r1 ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>( *(r1++), 2 ) << FAS_TESTING_FILE_LINE;
  t << is_false<expect>( r1 ) << FAS_TESTING_FILE_LINE;
}

template<typename R, typename T>
inline void output_test(T& t, R r1)
{
  using namespace ::fas::testing;
  t << is_true<expect>( r1 ) << FAS_TESTING_FILE_LINE;
  *(r1++) = 1;
  t << is_true<expect>( r1 ) << FAS_TESTING_FILE_LINE;
  *r1++ = 2;
}

template<typename R, typename T>
inline void forward_test(T& t, R r1)
{
  using namespace ::fas::testing;
  t << is_true<expect>( r1 ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>( *(r1++),  1 ) << FAS_TESTING_FILE_LINE;
  t << is_true<expect>( r1 ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>( *(r1++),  2 ) << FAS_TESTING_FILE_LINE;
  t << is_false<expect>( r1 ) << FAS_TESTING_FILE_LINE;
}



template<typename R, typename T>
inline void bidirectional_test(T& t, R r1)
{
  using namespace ::fas::testing;
  r1++;
  r1++;
  t << is_false<expect>( r1 ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>( *(--r1),  2 ) << FAS_TESTING_FILE_LINE;
  t << is_true<expect>( r1 ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>( *(r1--),  2 ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>( *r1,  1 ) << FAS_TESTING_FILE_LINE;
}

template<typename R, typename T>
inline void random_access_test(T& t, R r1)
{
  using namespace ::fas::testing;
  t << is_true<expect>( r1 ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>( *(r1 + 1),  2 ) << FAS_TESTING_FILE_LINE;
  R r_tmp = r1 + 1;
  t << is_true<expect>( r_tmp ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>( *r_tmp,  2 ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>( *(r_tmp - 1),  1 ) << FAS_TESTING_FILE_LINE;
  
  t << equal<expect>( r_tmp[0],  2 ) << FAS_TESTING_FILE_LINE;
  r_tmp[0] = 3;
  t << equal<expect>( r1[1],  3 ) << FAS_TESTING_FILE_LINE;
  r1[1] = 2;
  t << equal<expect>( r_tmp[0],  2 ) << FAS_TESTING_FILE_LINE;
}

template<typename R, typename T>
inline void random_access_const_test(T& t, R r1)
{
  using namespace ::fas::testing;
  t << is_true<expect>( r1 ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>( *(r1 + 1),  2 ) << FAS_TESTING_FILE_LINE;
  R r_tmp = r1 + 1;
  t << is_true<expect>( r_tmp ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>( *r_tmp,  2 ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>( *(r_tmp - 1),  1 ) << FAS_TESTING_FILE_LINE;
  
  t << is_true<expect>( r_tmp[0] == 2 ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>( r_tmp[0],  2 ) << FAS_TESTING_FILE_LINE;
}

