#ifndef FASLIB_TEST_SERIALIZATION_BAR_HPP
#define FASLIB_TEST_SERIALIZATION_BAR_HPP

#include "foo.hpp"

#include <cstring>
#include <string>
#include <vector>
#include <set>
#include <map>

struct foo_less
  : public std::binary_function<int,int,bool>
{
  bool operator() (const foo& a, const foo& b)
  {
    return a.foo1 < b.foo1;
  }
};

struct bar: foo
{
  struct baz
  {
    int baz1;
    baz(): baz1(42) {}
    baz(int): baz1(42) {}
  };

  baz bar1;
  foo bar2;
  std::vector<foo> bar3;
  typedef foo bar4type[2];
  bar4type bar4;
  typedef std::set<foo, foo_less> foo_set;
  foo_set bar5;
  typedef std::map<std::string, foo> foo_map;
  foo_map bar6;
  foo_map bar7;

  bar(): foo(), bar1(), bar2()
  {
    bar3.push_back(foo());
    bar4[0] = foo();
    bar4[1] = foo();

    foo f;
    f.foo1 = 1;
    bar5.insert(f);
    f.foo1 = 2;
    bar5.insert(f);
    bar6.insert( std::make_pair("bar6-1", foo()) );
    bar6.insert( std::make_pair("bar6-2", foo()) );
    bar7.insert( std::make_pair("bar7-1", foo()) );
    bar7.insert( std::make_pair("bar7-2", foo()) );
  }

  explicit bar(int): foo(0), bar1(0), bar2(0)
  {
    std::fill_n(bar4, sizeof(bar4)/sizeof(foo), foo());
  }

  const baz& get_baz() const { return bar1; }
  void set_baz( const baz& b) { bar1 = b; }
  const baz& baz_ref() const { return bar1; }
  baz& baz_ref() { return bar1; }
};


#endif

