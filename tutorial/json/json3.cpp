#include <fas/serialization/json/meta.hpp>
#include <fas/serialization/json/serializer.hpp>
#include <fas/serialization/json/deserializer.hpp>
#include <fas/range.hpp>

#include <iostream>
#include <vector>
#include <set>
#include <map>

namespace aj = fas::json;

int main()
{
  aj::serializer<> s;
  aj::deserializer<> ds;
  
  std::string jsonstring;
  std::map<std::string, std::string> dict;
  dict["key1"]="value1";
  dict["key2"]="value2";
  dict["key3"]="value3";
  
  std::cout << "JSON serialization: " << std::endl;
  s( aj::dict< std::string, aj::string >(), dict, fas::init_range(jsonstring) );
  std::cout << "Dictonary: " << jsonstring << std::endl;
  


  /// ////////////////////////////////////////////
  /// ////////////////////////////////////////////
  /// ////////////////////////////////////////////
  
  std::cout << std::endl;
  std::cout << "JSON deserialization: " << std::endl;

  
  std::cout << std::endl;
}
