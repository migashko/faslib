//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#include <iostream>
#include <fas/testing.hpp>
#include <fas/range.hpp>
#include <fas/static_check/static_check.hpp>
#include <string>
#include <vector>

typedef char array1_type[3][3][2];
typedef char array1_item_type[3][2];
array1_type array1 = {
  { {"1"}, {"2"}, {"3"} },
  { {"4"}, {"5"}, {"6"} },
  { {"7"}, {"8"}, {"9"} }
};

typedef char array2_type[9][2];
array2_type array2 = { {"1"}, {"2"}, {"3"}, {"4"}, {"5"}, {"6"}, {"7"}, {"8"}, {"9"} };
array2_type array2r1 = { {"9"}, {"8"}, {"7"}, {"6"}, {"5"}, {"4"}, {"3"}, {"2"}, {"1"} };
array2_type array2r2 = { {"7"}, {"8"}, {"9"}, {"4"}, {"5"}, {"6"}, {"1"}, {"2"}, {"3"} };
array2_type array2r2c = { "7", "8", "9", "4", "5", "6", "1", "2", "3" };

UNIT(array_range_unit, "")
{
  using namespace ::fas::testing;

  typedef fas::typerange<array1_type>::range r1i_type;
  typedef fas::typerange<array2_type>::range r2_type;

  r1i_type r1i = fas::range(array1);
  r2_type r2 = fas::range(array2);

  for ( ;r1i; ++r1i )
  {
    typedef fas::typerange< r1i_type::value_type>::range r2i_type;
    r2i_type r2i = fas::range( *r1i );
    for ( ;r2i; ++r2i )
    {
      t << equal<expect, std::string>( *r2i, *r2++ );
    }
  }
}

UNIT(array_rrange_unit, "")
{
  using namespace ::fas::testing;

  typedef fas::typerange<array2_type>::range r2_type;
  typedef fas::typerange<array2_type>::reverse_range r2r_type;

  r2_type r1 = fas::range(array2);
  r2r_type r2 = fas::rrange(array2r1);

  for ( ;r1 && r2; ++r1, ++r2 )
  {
    t << equal<expect, std::string>( *r1, *r2);
  }
}

UNIT(array_range2_unit, "")
{
  using namespace ::fas::testing;

  typedef fas::typerange<array1_type>::reverse_range r1i_type;
  typedef fas::typerange<array2_type>::range r2_type;

  r1i_type r1i = fas::rrange(array1);
  r2_type r2 = fas::range(array2r2);

  int c1 = 0;
  int c2 = 0;
  for ( int i1 = 0; r1i && i1< 99; ++r1i, ++i1, ++c1 )
  {
    typedef fas::typerange< r1i_type::value_type>::range r2i_type;
    r2i_type r2i = fas::range( *r1i );
    for ( int i2 = 0; r2i && i2 < 99; ++r2i, ++i2, ++c2 )
    {
      t << equal<expect, std::string>( *r2i, *r2++ );
    }
  }
  t << equal<expect, int>( c1 + 1, 4 ) << FAS_FL;
  t << equal<expect, int>( c2 + 1, 10 ) << FAS_FL;
  t << nothing;
}

UNIT(array_range3_unit, "")
{
  using namespace ::fas::testing;

  std::string first = *fas::begin( *fas::begin(array1) );
  t << equal<expect, std::string>( first, "1" )  << FAS_TESTING_FILE_LINE << std::endl << first;
  std::string last = *(fas::end( *(fas::end(array1)-1) )-1);
  t << equal<expect, std::string>( last, "9" )  << FAS_TESTING_FILE_LINE << std::endl << last;

  typedef fas::typerange<array1_type>::range array1_range;
  typedef fas::typerange<array1_item_type>::range array1_item_range;

  array1_range a1r = fas::range(array1);
  fas::decrease(++a1r,1,1);
  array1_item_range a1ri = fas::range(*a1r);
  fas::decrease(++a1ri,1,1);
  t << equal<expect, std::string>( *a1ri, "5" )  << FAS_TESTING_FILE_LINE << std::endl << *a1ri;

  fas::increase(a1r,1,1);
  ++a1r;
  fas::decrease(a1r,2,0);
  a1ri = fas::range(*a1r);
  fas::decrease(a1ri,0,2);
  t << equal<expect, std::string>( *a1ri, "7" )  << FAS_TESTING_FILE_LINE << std::endl << *a1ri;
  ++a1ri;
  t << is_false<expect>( a1ri )  << FAS_TESTING_FILE_LINE;
  ++a1r;
  t << is_false<expect>( a1r )  << FAS_TESTING_FILE_LINE;
}


UNIT(array_range4_unit, "")
{
  using namespace ::fas::testing;
  typedef fas::typerange<array2_type>::orange or2_type;
  or2_type or2r2 = fas::orange(array2r2);
  or2_type or2r2c = fas::orange(array2r2c);
  int i = 0;

  for ( ;or2r2 && or2r2c; ++or2r2, ++or2r2c, ++i )
    t << equal<expect, std::string>(*or2r2, *or2r2c);
  t << equal<expect, int>(i, 9);


  or2r2c = fas::orange(array2r2c, true);
  i = 0;
  for ( ;or2r2c; ++or2r2c, ++i )
    t << equal<expect, std::string>(*or2r2c, "") << *or2r2c;
  t << equal<expect, int>(i, 9);

}


UNIT(array_range5_unit, "")
{
  using namespace ::fas::testing;

  typedef fas::typerange<array1_type>::orange r1i_type;
  r1i_type r1i = fas::orange(array1, true);

  for ( ;r1i; ++r1i )
  {
    typedef fas::typerange< r1i_type::value_type>::range r2i_type;
    r2i_type r2i = fas::range( *r1i );
    for ( ;r2i; ++r2i )
    {
      t << equal<expect, std::string>( *r2i, "" );
    }
  }
}




BEGIN_SUITE(array_range_suite, "")
  ADD_UNIT(array_range_unit)
  ADD_UNIT(array_rrange_unit)
  ADD_UNIT(array_range2_unit)
  ADD_UNIT(array_range3_unit)
  ADD_UNIT(array_range4_unit)
  ADD_UNIT(array_range5_unit)
END_SUITE(array_range_suite)
