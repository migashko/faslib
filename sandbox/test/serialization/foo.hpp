#ifndef FASLIB_TEST_SERIALIZATION_FOO_HPP
#define FASLIB_TEST_SERIALIZATION_FOO_HPP

#include <cstring>
#include <string>
#include <vector>
#include <algorithm>

struct foo
{
  int foo1;
  std::string foo2;
  
  typedef char foo3type[20];
  foo3type foo3;
  //char foo3[20];

  std::vector<int> foo4;
  typedef int foo5type[5];
  foo5type foo5;
  std::vector<std::string> foo6;

  foo()
    : foo1(-1)
    , foo2("test-foo2")
  {
    std::strcpy(foo3, "test-foo3");
    foo4.push_back(20);
    foo4.push_back(30);
    foo4.push_back(40);
    
    for (size_t i = 0 ; i < sizeof(foo5type)/sizeof(int); ++i )
    {
      foo5[i] = i;
    }
    
    foo6.push_back("test-foo6-1");
    foo6.push_back("test-foo6-2");
  }
  
  foo(int)
    :foo1()
  {
    std::fill_n(foo3, sizeof(foo3),'\0');
    std::fill_n(foo5, sizeof(foo5type)/sizeof(int), 0);
  }
  
  bool operator == (const foo& f) const
  {
    return foo1 == f.foo1
           && foo2 == f.foo2
           && ( std::strcmp(foo3, f.foo3) == 0 )
           && foo4 == f.foo4
           && ( std::memcmp(foo5, f.foo5, sizeof(foo5) ) == 0) 
           && foo6 == f.foo6;
  }
};


#endif
