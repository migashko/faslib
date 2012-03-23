#include <fas/range.hpp>
#include <fas/xtime.hpp>
#include <cstring>
#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>

using namespace fas;

#define LIMIT_OP 100000000


template<typename R>
void initialize( R r, std::size_t size )
{
  //std::cout << r.distance() << std::endl;
  
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
  initialize(init_range(array1), LIMIT_OP);
  finish = process_nanotime();
  std::cout << "init array1: " << finish - start << std::endl;
  
  start = process_nanotime();
  initialize(init_range(array2), LIMIT_OP);
  finish = process_nanotime();
  std::cout << "init array2: " << finish - start << std::endl;
  
  start = process_nanotime();
  initialize(init_range(vect1), LIMIT_OP);
  finish = process_nanotime();
  std::cout << "init vect1: " << finish - start << std::endl;
  
  start = process_nanotime();
  initialize(init_range(vect2), LIMIT_OP);
  finish = process_nanotime();
  std::cout << "init vect1: " <<  finish - start << std::endl;
  
  start = process_nanotime();
  std::sort( array1, array1 + LIMIT_OP);
  finish = process_nanotime();
  std::cout << "sort array1: " <<  finish - start << std::endl;

  start = process_nanotime();
  std::sort( fas::range(array2), fas::end_range(array2) );
  finish = process_nanotime();
  std::cout << "sort array2: " <<  finish - start << std::endl;

  start = process_nanotime();
  std::sort( vect1.begin(), vect1.end());
  finish = process_nanotime();
  std::cout << "sort vect1: " <<  finish - start << std::endl;

  start = process_nanotime();
  std::sort( fas::range(vect2), fas::end_range(vect2) );
  finish = process_nanotime();
  std::cout << "sort vect2: " <<  finish - start << std::endl;
  std::cout << std::endl;
}}
