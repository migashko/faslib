#ifndef FAS_JSONRPC_INVOKE_PARSE_OBJECT_HPP
#define FAS_JSONRPC_INVOKE_PARSE_OBJECT_HPP

#include <fas/jsonrpc/tags.hpp>
#include <fas/jsonrpc/aspect.hpp>

#include <fas/jsonrpc/json/raw_object.hpp>
#include <fas/jsonrpc/json/raw_object_json.hpp>

#include <fas/aop/aspect.hpp>
#include <fas/aop/advice.hpp>
#include <fas/type_list/type_list_n.hpp>

namespace fas{ namespace jsonrpc{
  

struct ad_parse_object
{
  template<typename T, typename R>
  R operator()(T& t, R r )
  {
    typedef typename T::aspect::template advice_cast<_deserializer_>::type deserializer;
    deserializer ds;

#warning: TODO: выбор объекта по типу range
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
