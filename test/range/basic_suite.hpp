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

  t << equal<expect>( *r1, 1 ) << "*r1 == 1";
  *r1 = 2;
  t << equal<expect>( *r1, 2 ) << "*r1 == 2";
  t << equal<assert>( r1.operator ->(), &(*r1) ) << "r1.operator ->() == &(*r1)" << stop;
  *(r1.operator ->() ) = 3;
  t << equal<expect>( *r1, 3 ) << "*r1 == 3";
  *r1 = 1;
  
  R r_tmp = r1;
  t << equal<expect>( r1, r_tmp ) << "r1 == r_tmp";
  t << equal<expect>( &(*r1), &(*r_tmp) ) << "&(*r1) == &(*r_tmp)";
}

template<typename R, typename T>
inline void trivial_const_test(T& t, R r1)
{
  using namespace ::fas::testing;
  t << equal<expect>( *r1, 1 ) << "*r1 == 1";
  R r_tmp = r1;
  t << equal<expect>( r1, r_tmp ) << "r1 == r_tmp";
  t << equal<expect>( &(*r1), &(*r_tmp) ) << "&(*r1) == &(*r_tmp)";
}

template<typename R, typename T>
inline void input_test(T& t, R r1)
{
  using namespace ::fas::testing;
  
  t << is_true<expect>( r1 ) << "input_test(1): r1 == true ";
  t << is_true<expect>( *r1 == 1 ) << "input_test(2): *r1 == 1 [[" << *r1;
  ++r1;
  t << is_true<expect>( r1 ) << "input_test(3): r1 == true ";
  t << equal<expect>( *(r1++), 2 ) << "input_test(4): *r1 == 2 [[ " << *r1;
  t << is_false<expect>( r1 ) << "input_test(4): r1 == false ";
}

template<typename R, typename T>
inline void output_test(T& t, R r1)
{
  using namespace ::fas::testing;
  t << is_true<expect>( r1 ) << " r1 == true ";
  *(r1++) = 1;
  t << is_true<expect>( r1 ) << " r1 == true ";
  *r1++ = 2;
}

template<typename R, typename T>
inline void forward_test(T& t, R r1)
{
  using namespace ::fas::testing;
  t << is_true<expect>( r1 ) << " (1) r1 == true ";
  t << equal<expect>( *(r1++),  1 ) << "*(r1++) == 1";
  t << is_true<expect>( r1 ) << " (2) r1 == true ";
  t << equal<expect>( *(r1++),  2 ) << "*(r1++) == 2";
  t << is_false<expect>( r1 ) << " r1 == false ";
}



template<typename R, typename T>
inline void bidirectional_test(T& t, R r1)
{
  using namespace ::fas::testing;
  r1++;
  r1++;
  t << is_false<expect>( r1 ) << " r1 == false ";
  t << equal<expect>( *(--r1),  2 ) << "*(--r1) == 2";
  t << is_true<expect>( r1 ) << " r1 == true ";
  t << equal<expect>( *(r1--),  2 ) << "*(r1--) == 2";
  t << equal<expect>( *r1,  1 ) << "*r1 == 1";
}

template<typename R, typename T>
inline void random_access_test(T& t, R r1)
{
  using namespace ::fas::testing;
  t << is_true<expect>( r1 ) << " r1 == false ";
  t << equal<expect>( *(r1 + 1),  2 ) << "*(--r1) == 2";
  R r_tmp = r1 + 1;
  t << is_true<expect>( r_tmp ) << " r1 == true ";
  t << equal<expect>( *r_tmp,  2 ) << "*(r1--) == 2";
  t << equal<expect>( *(r_tmp - 1),  1 ) << "*r1 == 1";
  
  t << equal<expect>( r_tmp[0],  2 ) << "r_tmp[0] == 2 " << r_tmp[0];
  r_tmp[0] = 3;
  t << equal<expect>( r1[1],  3 ) << "r1[1] = 3";
  r1[1] = 2;
  t << equal<expect>( r_tmp[0],  2 ) << "r_tmp[0] == 2";
}

template<typename R, typename T>
inline void random_access_const_test(T& t, R r1)
{
  using namespace ::fas::testing;
  t << is_true<expect>( r1 ) << " r1 == false ";
  t << equal<expect>( *(r1 + 1),  2 ) << "*(--r1) == 2";
  R r_tmp = r1 + 1;
  t << is_true<expect>( r_tmp ) << " r1 == true ";
  t << equal<expect>( *r_tmp,  2 ) << "*(r1--) == 2";
  t << equal<expect>( *(r_tmp - 1),  1 ) << "*r1 == 1";
  
  t << is_true<expect>( r_tmp[0] == 2 ) << "r_tmp[0] == 2 " << r_tmp[0];
  t << equal<expect>( r_tmp[0],  2 ) << "r_tmp[0] == 2 " << r_tmp[0];
}

