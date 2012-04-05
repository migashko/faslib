#include <fas/testing.hpp>
#include <fas/range.hpp>
#include <fas/static_check/static_check.hpp>

typedef char array1_type[3][3][2];
array1_type array1 = {
  { {"1"}, {"2"}, {"3"} },
  { {"4"}, {"5"}, {"6"} },
  { {"7"}, {"8"}, {"9"} }
};

typedef char array2_type[9][2];
array2_type array2 = { {"1"}, {"2"}, {"3"}, {"4"}, {"5"}, {"6"}, {"7"}, {"8"}, {"9"} };
array2_type array2r1 = { {"9"}, {"8"}, {"7"}, {"6"}, {"5"}, {"4"}, {"3"}, {"2"}, {"1"} };
array2_type array2r2 = { {"7"}, {"8"}, {"9"}, {"4"}, {"5"}, {"6"}, {"1"}, {"2"}, {"3"} };

UNIT(array_range_test, "")
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
      std::cout << *r2i << std::endl;
      t << equal<expect, std::string>( *r2i, *r2++ );
    }
  }
};

UNIT(array_rrange_test, "")
{
  using namespace ::fas::testing;
  
  typedef fas::typerange<array2_type>::range r2_type;
  typedef fas::typerange<array2_type>::reverse_range r2r_type;
  
  r2_type r1 = fas::range(array2);
  r2r_type r2 = fas::rrange(array2r1);
  
  for ( ;r1 && r2; ++r1, ++r2 )
  {
    std::cout << *r1 << "="<< *r2 <<  std::endl;
    t << equal<expect, std::string>( *r1, *r2);
  }
};

UNIT(array_range2_test, "")
{
  using namespace ::fas::testing;
  
  typedef fas::typerange<array1_type>::reverse_range r1i_type;
  typedef fas::typerange<array2_type>::range r2_type;
  
  r1i_type r1i = fas::rrange(array1);
  r2_type r2 = fas::range(array2r2);
  
  for ( ;r1i; ++r1i )
  {
    typedef fas::typerange< r1i_type::value_type>::range r2i_type;
    r2i_type r2i = fas::range( *r1i );
    for ( ;r2i; ++r2i )
    {
      std::cout << std::endl << *r2i << "==" << *r2;
      t << equal<expect, std::string>( *r2i, *r2++ );
    }
  }
};



BEGIN_SUITE(array_range_suite, "")
  ADD_UNIT(array_range_test)
  ADD_UNIT(array_rrange_test)
  ADD_UNIT(array_range2_test)
END_SUITE(array_range_suite)
