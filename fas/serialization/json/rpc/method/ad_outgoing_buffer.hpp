#ifndef FAS_SERIALIZATION_JSON_RPC_METHOD_AD_OUTGOING_BUFFER_HPP
#define FAS_SERIALIZATION_JSON_RPC_METHOD_AD_OUTGOING_BUFFER_HPP

#include <fas/serialization/json/rpc/method/tags.hpp>
#include <fas/range/.hpp>
#include <vector>

namespace fas{ namespace json{ namespace rpc{ namespace method{


template<typename C = std::vector<char> >
struct ad_outgoing_buffer
{
  typedef C buffer_type;
  buffer_type buffer;
  
  typedef typename range_traits<C>::initial_range_type initial_range_type;
  typedef typename range_traits<C>::type range_type;
  
  template<typename T>
  void clear(T&) 
  {
    buffer.clear(); 
  }
  
  initial_range_type get_initial_range()
  {
    return (buffer);
  }

  range_type get_range()
  {
    return (buffer);
  }
};


}}}}

#endif

