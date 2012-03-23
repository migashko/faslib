#ifndef FAS_SERIALIZATION_JSON_RPC_RESPONSE_OBJECT_HPP
#define FAS_SERIALIZATION_JSON_RPC_RESPONSE_OBJECT_HPP

#include <vector>
#include <algorithm>


namespace fas{ namespace json{ namespace rpc{
  
// не нужен
template<typename P>
struct response_object_temp
{
  typedef P response_type;
  typedef char version_type[8];
  
  int id;
  version_type version;
  response_type result;
  
  response_object_temp()
    : id(1)
    , result()
  {
  }
};

template<typename R>
struct response_object_t
{
  typedef R range_type;
  int id;
  range_type result;
};

/*
struct response_object: response_object_t<char> {};
struct wresponse_object: response_object_t<wchar_t> {};
*/

  
}}}

#endif
