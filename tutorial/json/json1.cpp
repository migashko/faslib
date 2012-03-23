#include <fas/serialization/json/meta.hpp>
#include <fas/serialization/json/serializer.hpp>
#include <fas/serialization/json/deserializer.hpp>
#include <fas/range.hpp>

#include <iostream>

namespace aj = fas::json;

int main()
{
  aj::serializer<> s;
  aj::deserializer<> ds;
  std::string jsonstring;
  
  std::cout << "JSON serialization: " << std::endl;
  
  std::cout << "integer -12345: ";
  s( aj::integer(), -12345, fas::init_range(jsonstring) );
  std::cout << jsonstring << std::endl;
  jsonstring.clear();

  std::cout << "real 3.14: ";
  s( aj::real(), 3.14, fas::init_range(jsonstring) );
  std::cout << jsonstring << std::endl;
  jsonstring.clear();

  std::cout << "boolean true: ";
  s( aj::boolean(), true, fas::init_range(jsonstring) );
  std::cout << jsonstring << std::endl;
  jsonstring.clear();

  std::cout << "simple string \"hello world\": ";
  s( aj::string(), "hello world", fas::init_range(jsonstring) );
  std::cout << jsonstring << std::endl;
  jsonstring.clear();

  std::cout << "tabbed string \"hello	world\": ";
  s( aj::string(), "hello	world", fas::init_range(jsonstring) );
  std::cout << jsonstring << std::endl;
  jsonstring.clear();

  /// ////////////////////////////////////////////
  /// ////////////////////////////////////////////
  /// ////////////////////////////////////////////
  
  std::cout << std::endl;
  std::cout << "JSON deserialization: " << std::endl;
  
  int intval = 0;
  jsonstring = "-12345";
  ds( aj::integer(), intval, fas::range(jsonstring) );
  std::cout << "integer \"-12345\": " << intval << std::endl; 

  float realval = 0.0;
  jsonstring = "3.14";
  ds( aj::real(), realval, fas::range(jsonstring) );
  std::cout << "real \"3.14\": " << realval << std::endl; 

  bool boolval = false;
  jsonstring = "true";
  ds( aj::boolean(), boolval, fas::range(jsonstring) );
  std::cout << "boolean \"true\": " << boolval << std::endl; 

  std::string strval;
  jsonstring = "\"hello world\"";
  ds( aj::string(), strval, fas::range(jsonstring) );
  std::cout << "simple string \"hello world\": " << strval << std::endl; 
  
  strval.clear();
  jsonstring = "\"hello\tworld\"";
  ds( aj::string(), strval, fas::range(jsonstring) );
  std::cout << "tabbed string \"hello\\tworld\": " << strval << std::endl; 
}
