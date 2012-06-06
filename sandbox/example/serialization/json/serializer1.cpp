#include <fas/typemanip/tstring.hpp>
#include <fas/serialization/json/meta.hpp>
#include <fas/serialization/json/ser/serializer.hpp>

#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <cstring>

namespace aj = ::fas::json;
namespace ajs = ::fas::json::ser;

struct object1
{
  int int1;
  std::string string1;
  char string2[200];
  
  object1()
    : int1(0)
  {
    std::fill_n(string2, 200, '\0');
  }

  object1(int i1, const std::string& s1, const char* s2)
    : int1(i1)
    , string1(s1)
  {
    std::strcpy(string2, s2);
  }

};

bool operator < (const object1& left, const object1& right)
{
  return left.int1 < right.int1;
};

struct object2
  : object1
{
  std::vector<int> vect1;
  int arr1[5];
  std::set<std::string> set1;
};

struct object3
{
  object1 arrobj1[3];
  std::set<object1> setobj1;
  std::map<std::string, object2> mapobj2;
  
  typedef std::map<std::string, std::string> other_type;
  other_type other;

  typedef std::map<std::string, int> other_type2;
  other_type2 other2;

};

FAS_NAME(int1)
FAS_NAME(string1)
FAS_NAME(string2)
FAS_NAME(setobj1)


template< typename T, typename M, typename C = std::map< std::string, T >  >
struct map_field
{
  typedef C container;
  typedef typename container::value_type value_type;
  typedef typename value_type::first_type first_type;
  typedef typename value_type::second_type second_type;
  
  typedef aj::member<
            aj::attr<
              value_type, 
              first_type, 
              &value_type::first, 
              aj::string
            >,
            aj::attr<
              value_type,
              second_type,
              &value_type::second,
              M
            >
          > type;

};

template<typename V, typename VT, VT V::* m, typename M>
struct attr_map
{
  typedef aj::attr<
      V,
      VT,
      m,
      aj::sequence< typename map_field<std::string, M, VT>::type    >
  > type;

};



typedef aj::object<
  fas::type_list_n<
    aj::member< n_int1, aj::attr< object1, int, &object1::int1, aj::integer > >,
    aj::member< n_string1, aj::attr< object1, std::string, &object1::string1, aj::string > >,
    aj::member< n_string2, aj::attr< object1, char[200], &object1::string2, aj::string > >
  >::type
> object1_json;

typedef aj::object<
  aj::brute_pair<
  fas::type_list_n<
    // object1_json::first_metatype,
    aj::member< n_setobj1, aj::attr< object3, std::set<object1>, &object3::setobj1, aj::array<object1_json> > >
  >::type,
  fas::type_list_n<
    attr_map<object3, object3::other_type, &object3::other, aj::string >::type,
    attr_map<object3, object3::other_type2, &object3::other2, aj::integer >::type
    /*
    aj::attr<
      object3,
      object3::other_type,
      &object3::other,
      aj::sequence<
        map_field<std::string, aj::string>::type
        
        aj::field<
          aj::attr<
            object3::other_type::value_type, 
            object3::other_type::value_type::first_type, 
            &object3::other_type::value_type::first, 
            aj::string 
          >,
          aj::attr<
            object3::other_type::value_type,
            object3::other_type::value_type::second_type,
            &object3::other_type::value_type::second,
            aj::string
          >
        >
      >
    > */
  >::type
  >
> object3_json;

int main()
{
  object1 obj1(42, "one", "three");
  obj1.int1 = 42;
  ajs::serializer<> serializer;
  serializer( object1_json(), obj1, fas::( std::ostreambuf_iterator<char>(std::cout) ) );
  std::cout << std::endl;
  
  object3 obj3;
  obj3.setobj1.insert(obj1);
  obj3.other["other1"]="value1";
  obj3.other["other2"]="value2";
  obj3.other["other3"]="value3";
  obj3.other2["other21"]=21;
  obj3.other2["other22"]=22;
  obj3.other2["other23"]=23;
  serializer( object3_json(), obj3, fas::( std::ostreambuf_iterator<char>(std::cout) ) );
  std::cout << std::endl;
  return 0;
}
