#ifndef FAS_JSONRPC_INVOKE_AD_PARSE_OTHER_ERROR_HPP
#define FAS_JSONRPC_INVOKE_AD_PARSE_OTHER_ERROR_HPP

#include <fas/jsonrpc/invoke/tags.hpp>

namespace fas{ namespace jsonrpc{ 

template< typename J = custom_error_json, typename V = custom_error >
struct ad_parse_other_error
{
  template<typename T, typename RP>
  void operator() (T& t, RP error_range)
  {
    typedef typename T::aspect::template advice_cast<_deserializer_>::type deserializer;
    deserializer ds;

    V error_object;
    if ( ds( J(), error_object, error_range ) );
      t.get_aspect().template get< _other_error_handler_ >()( t, error_object );
    else
      t.get_aspect().template get< _other_error_parse_error_ >()( t, error_object );

  }
};


}}

#endif
