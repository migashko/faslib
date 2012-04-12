#include <fas/range.hpp>
#include <fas/xtime.hpp>
#include <cstring>
#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>

using namespace fas;

#ifdef NDEBUG
#define LIMIT_OP 10000000
#else
#define LIMIT_OP 10000
#endif


template<typename R>
void initialize( R r, std::size_t size )
{
  for ( std::size_t i = 0 ; i < size; ++i)
    *(r++) = i % 100;
  
};

int array1[LIMIT_OP];
int array2[LIMIT_OP];

std::vector<int> vect1(LIMIT_OP);
std::vector<int> vect2(LIMIT_OP);

int main() { for (int i =0; i < 3; ++i) {

  nanospan start;
  nanospan finish;

  vect1.clear();
  vect2.clear();

  start = process_nanotime();
  initialize(array1, LIMIT_OP);
  finish = process_nanotime();
  std::cout << "init array1: " << finish - start << std::endl;
  
  start = process_nanotime();
  initialize(orange(array2), LIMIT_OP);
  finish = process_nanotime();
  std::cout << "init orange(array2): " << finish - start << std::endl;
  
  
  vect1.resize(LIMIT_OP);
  start = process_nanotime();
  initialize(vect1.begin(), LIMIT_OP);
  finish = process_nanotime();
  std::cout << "init vect1.begin(): " << finish - start << std::endl;
  
  vect1.reserve(LIMIT_OP);
  start = process_nanotime();
  initialize(orange(vect2), LIMIT_OP);
  finish = process_nanotime();
  std::cout << "init orange(vect2): " <<  finish - start << std::endl;

  start = process_nanotime();
  initialize(range(vect2), LIMIT_OP);
  finish = process_nanotime();
  std::cout << "init range(vect2): " <<  finish - start << std::endl;

  start = process_nanotime();
  std::sort( array1, array1 + LIMIT_OP);
  finish = process_nanotime();
  std::cout << "sort array1: " <<  finish - start << std::endl;

  start = process_nanotime();
  std::sort( fas::range(array2), fas::erange(array2));
  finish = process_nanotime();
  std::cout << "sort fas::range(array2): " <<  finish - start << std::endl;

  start = process_nanotime();
  std::sort( vect1.begin(), vect1.end());
  finish = process_nanotime();
  std::cout << "sort vect1.begin(): " <<  finish - start << std::endl;

  start = process_nanotime();
  std::sort( fas::range(vect2), fas::erange(vect2));
  finish = process_nanotime();
  std::cout << "sort fas::range(vect2): " <<  finish - start << std::endl;
  
  std::cout << std::endl;
}}
