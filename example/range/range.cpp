#include <iostream>
#include <vector>
#include <sstream>
#include <fas/range.hpp>


#include <boost/range/algorithm.hpp>

using namespace fas;

template<typename R>
void init_range(R r)
{
  for (int i = 0 ; i < 10 && r; ++i, ++r)
    *r = '0' + i;
};

template<typename R>
void show_range(R r)
{
  if (r)
    std::cout << *r++;
  for ( ; r ; ++r)
    std::cout << ", " << *r ;
  std::cout << std::endl;
};


int main()
{
  char arr[4]={0};
  //init_range( <int[4]>(arr) );
  init_range( (arr) );
  show_range( (arr) );
  
  std::vector<char> vect(5);
  init_range( (vect) );
  show_range( (vect) );
  vect.clear();
  init_range( ( std::back_inserter(vect) ) );
  show_range( (vect) );
  show_range( (vect.begin() + 2, vect.begin() + 7) );
  show_range( (vect.rbegin() + 2, vect.rbegin() + 7) );
  
  std::stringstream ss;
  // init_range( (ss) ); // ERROR
  init_range( (std::ostreambuf_iterator<char>(ss) ) ); // OK
  //show_range( (std::istreambuf_iterator<char>(ss) ) ); // ERROR
  show_range( (std::istreambuf_iterator<char>(ss), std::istreambuf_iterator<char>() ) ); // OK

  const char* str="345678";
  // show_range( (str) ); // ERROR
  show_range( make_string_range(str) ); // OK
  
  const char arrstr[]="4567";
  show_range( (arrstr) ); // OK
  
  
  random_access_range< /*std::vector<char>::iterator*/char* > r = (arr);
  *(r.begin())='0'+9;
  show_range( (arr) );
  //random_access_range< char* >::iterator itr1;
  //itr1 = r.begin();
  //random_access_range< char* >::iterator itr2 = r.end();
  /*boost::range_mutable_iterator< random_access_range< char* > > rmi;
   * */
  ///boost::sort( r );
  //show_range( <int[4]>(arr) );
  return 0;
}