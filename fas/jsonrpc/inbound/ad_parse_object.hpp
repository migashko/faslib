#ifndef FAS_JSONRPC_INBOUND_AD_PARSE_OBJECT_HPP
#define FAS_JSONRPC_INBOUND_AD_PARSE_OBJECT_HPP

#include <fas/jsonrpc/inbound/error/tags.hpp>
#include <fas/jsonrpc/inbound/tags.hpp>


#include <fas/jsonrpc/inbound/types/raw_object.hpp>
#include <fas/jsonrpc/inbound/json/raw_object_json.hpp>

namespace fas{ namespace jsonrpc{
  

struct ad_parse_object
{
  template<typename T, typename R>
  R operator()(T& t, R r )
  {
    typedef typename T::aspect::template advice_cast<_deserializer_>::type deserializer;
    deserializer ds;

//#warning: TODO: выбор объекта по типу range
    raw_object obj;
    r = ds(raw_object_json(), obj, r);

    if ( ds && obj.is_valid() )
    {
      t.get_aspect().template get<_process_object_>()(t, obj);
    }
    else if ( obj.has_id() )
    {
      t.get_aspect().template get<_invalid_request_>()(t, obj.id );
    }
    else
    {
      t.get_aspect().template get<_invalid_request_>()(t);
    }
    
    return r;
  }
};

}}

#endif

