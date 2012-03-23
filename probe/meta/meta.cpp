#include <fas/type_list/type_list_n.hpp>
#include <fas/aop/aspect.hpp>

using namespace fas;

template<typename ST, typename T = ST, typename A = aspect<> >
struct meta_access
{
  typedef T value_type;
  typedef ST serialize_type;
  typedef ST unserialize_type;
  void set_value(const T& value)
  {
    
  }
};

template<typename T>
struct number
{
  /*typedef _integer_ serializer_tag; 
  typedef _integer_ deserializer_tag;
  typedef _number_ parser_tag;
  typedef getter getter_type;
  typedef setter setter_type;
  */
};

template<typename T>
struct string
{
};

template<int N, typename T>
struct string< T[N] >
{
};

int main()
{
  int a = 10;
  double b = 0.1;
  a = b;
  
  //string<char[10]> c;
  return a;
}