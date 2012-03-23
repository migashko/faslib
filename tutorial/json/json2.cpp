#include <fas/serialization/json/meta.hpp>
#include <fas/serialization/json/serializer.hpp>
#include <fas/serialization/json/deserializer.hpp>
#include <fas/range.hpp>

#include <iostream>
#include <vector>
#include <set>

namespace aj = fas::json;

int main()
{
  using namespace ::fas;
  using namespace ::fas::json;
  
  aj::serializer<> s;
  aj::deserializer<> ds;
  std::string jsonstring;
  
  std::cout << "JSON serialization: " << std::endl;

  int arr1[]={1,2,3,4};
  s( aj::array<aj::integer>(), arr1, fas::init_range(jsonstring) );
  std::cout << "int arr1[]={1,2,3,4}: " << jsonstring << std::endl;
  jsonstring.clear();
  
  char arr2[4][8] = { "a", "bb", "ccc", "ddd" };
  s( aj::array< aj::string >(), arr2, fas::init_range(jsonstring) );
  std::cout << "char arr2[4][8]={\"a\",\"bb\",\"ccc\",\"ddd\"}: " << jsonstring << std::endl;
  jsonstring.clear();
  
  std::vector<float> vect1;
  vect1.push_back(1.0);
  vect1.push_back(1.1);
  vect1.push_back(1.2);
  s( aj::array< aj::real>(), vect1, fas::init_range(jsonstring) );
  std::cout << "std::vector<float>: " << jsonstring << std::endl;
  jsonstring.clear();
  
  std::multiset< std::vector<float> > set1;
  set1.insert(vect1);
  set1.insert(vect1);
  set1.insert(vect1);
  s( aj::array< aj::array< aj::real> >(), set1, fas::init_range(jsonstring) );
  std::cout << "std::multiset< std::vector<float> >: " << jsonstring << std::endl;

  /// ////////////////////////////////////////////
  /// ////////////////////////////////////////////
  /// ////////////////////////////////////////////
  
  std::cout << std::endl;
  std::cout << "JSON deserialization: " << std::endl;

  
  jsonstring = "[5,6,7]";
  std::cout << jsonstring << ":";
  ds( aj::array< aj::integer >(), arr1, fas::range(jsonstring) );
  for (int i = 0; i < 4; ++i )
  {
    if ( i!=0 ) std::cout << ',';
    std::cout << arr1[i];
  }
  std::cout << std::endl;
  
  jsonstring = "[\"0123456\",\"dddd\",\"cccc\",\"bbbb\"]";
  std::cout << jsonstring << ":";
  ds( aj::array< aj::string >(), arr2, fas::range(jsonstring) );
  for (int i = 0; i < 4; ++i )
  {
    if ( i!=0 ) std::cout << ',';
    std::cout << arr2[i];
  }
  std::cout << std::endl;

  jsonstring = "[ [3.1,3.2,3.3,4.1,4.2,4.3], [5.1,5.2,5.3] ]";
  set1.clear();
  ds( aj::array< aj::array< aj::real> >(), set1, fas::range(jsonstring) );
  std::multiset< std::vector<float> >::iterator itr = set1.begin();
  for ( ;itr!=set1.end();++itr)
  {
    if ( itr!=set1.begin() ) std::cout << ',';
    std::cout << "[";
    for (size_t i = 0; i < itr->size(); i++)
    {
      if ( i!=0 ) std::cout << ',';
      std::cout << (*itr)[i];
    }
    std::cout << "]";
  }
  std::cout << std::endl;
}
