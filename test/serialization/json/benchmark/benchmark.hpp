#ifndef TEST_SERIALISATION_JSON_BENCHMARK_BENCHMARK_HPP
#define TEST_SERIALISATION_JSON_BENCHMARK_BENCHMARK_HPP

#include <fas/xtime.hpp>
#include <vector>
#include <algorithm>
#include <numeric>

#ifdef NDEBUG
#define TOTAL_OP 10000000
#else
#define TOTAL_OP 1000
#endif
#define ONE_TIME_OP 1000
#define RNG 10

#define MAX_BUF 1024
typedef char buffer_type[MAX_BUF];

typedef fas::nanospan span_type;
typedef std::vector< span_type > span_list;


struct Person
{
  int id;
  std::string name;
  std::string email;

  Person(): id(0)
  {
    name.reserve(32);
    email.reserve(256);
  }

  void clear()
  {
    id = 0;
    name.clear();
    email.clear();
  }
};


struct Person2
{
  typedef char name_type[50];
  typedef char email_type[260];
  int id;
  char name[50];
  char email[260];

  Person2(): id(0){}

  void set_name(const name_type n)
  {
    std::strcpy( name, n );
  }

  const char* get_name() const
  {
    return name;
  }

  void set_email(const email_type n)
  {
    std::strcpy( email, n );
  }

  const char* get_email() const
  {
    return email;
  }
  
};

/*
span_type benchmark( span_list sl )
{
  std::sort(sl.begin(), sl.end() );
  size_t offset = sl.size()/RNG;
  if ( offset*2 < sl.size()  )
    sl = span_list( sl.begin() + offset, sl.end() - offset );

  return std::accumulate( sl.begin(), sl.end(), span_type() ) / static_cast<long>();
}
*/


#endif
