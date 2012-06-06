#ifndef FAS_SERIALIZATION_JSON_RPC_AD_INVOKE_HPP
#define FAS_SERIALIZATION_JSON_RPC_AD_INVOKE_HPP

#include <fas/serialization/json/parser/tags.hpp>
#include <fas/serialization/json/rpc/tags.hpp>
#include <fas/serialization/json/rpc/method/tags.hpp>
#include <fas/serialization/json/rpc/raw_object.hpp>
#include <fas/serialization/json/rpc/raw_object_json.hpp>
#include <fas/serialization/json/rpc/response_object.hpp>
#include <fas/serialization/json/rpc/response_object_json.hpp>

#include <iostream>

namespace fas{ namespace json{ namespace rpc{
  
template<typename R>
struct f_invoke
{
  const R& request_object;
  bool ready;
  typedef typename R::name_range_type name_range_type;
  // name_range_type name_range;
  f_invoke(const R& request_object)
    : request_object(request_object)
    , ready(false)
    // , name_range(request_object.name_range)
  {
    
  }
  
  template<typename T, typename AD>
  void operator()(T& t, AD& adv)
  {
    std::cout << "f_invoke: " << adv.name() << std::endl;

    if (ready) return;
    
    if ( !adv.check_name( request_object.name_range() ) )
      return;
    
    ready = true;

    if ( request_object.is_request() )
    {
      std::cout << "\tis_request"<< std::endl;
      std::cout << std::string(request_object.params.begin(), request_object.params.end() ) << std::endl;
      adv.invoke_request(t, (request_object.params), request_object.id );
    }
    else if ( request_object.is_notify() )
    {
      std::cout << "\tis_notify"<< std::endl;
    }
    else if ( request_object.is_response() )
    {
      std::cout << "\tis_response"<< std::endl;
    }
    else if ( request_object.is_error() )
    {
      std::cout << "\tis_error"<< std::endl;
    }
    else
    {
      std::cout << "\tnot valid"<< std::endl;
    }
  
    // Взять range для имени
    // проверка имени или id 
  }
};

struct ad_outgoing_result
{
  template<typename T, typename R>
  void operator()(T& t, R result, int id)
  {
    typedef response_object_t< R > response_object_type;
    typedef typename response_object_type::range_type range_type;
    
    response_object_type ro;
    ro.id = id;
    ro.result = result;
    
    typedef response_object_json_t<response_object_type> response_json;
    
    std::string tmp;
    typedef typename T::aspect::template advice_cast<_serializer_>::type serializer;
    
    serializer ser;
    ser( response_json(), ro, (tmp) );
    std::cout << "ad_outgoing_response: " << tmp << std::endl;
  }
};

struct ad_invoke_method
{
  template<typename T, typename R>
  R operator()(T& t, R r)
  {
    /*
    typedef typename T::aspect::template advice_cast<method::_invoke_request_>::type request_object;
    typedef typename T::aspect::template advice_cast<method::_invoke_request_json_>::type request_object_json;
    */
    typedef typename T::aspect::template advice_cast<_deserializer_>::type deserializer;
    
    
    // TODO: объект request_object брать из _request_object
    // неа. определяем тип request_object из ходя из типа R (range)
    deserializer deser;
    raw_object ro;
    r = deser(raw_object_json(), ro, r);
    
    if ( ro.is_error() && !ro.has_id() )
    {
      // пришла ошибка без идентификатора
      // отработать отдельно или передать последнему отправившему? 
      // если последнему, то не факт что ему при асинхронном взаимодействии 
    }
    //typedef request_object::name_range_type name_range_type;
    t.get_aspect().template getg<_method_>().for_each(t, f_invoke<raw_object>(ro) );
    return r;
  }
  
};

struct ad_invoke_batch
{
  template<typename T, typename R>
  R operator()(T& t, R r)
  {
    return r;
  }
};

struct ad_invoke
{
  template<typename T, typename R>
  R operator()(T& t, R r)
  {
    if ( t.get_aspect().template get<_deserializer_>().get_aspect().template get<parse::_object_>().check(r) )
      return t.get_aspect().template get<_invoke_method_>()(t, r);
    else if ( t.get_aspect().template get<_deserializer_>().get_aspect().template get<parse::_array_>().check(r) )
      return t.get_aspect().template get<_invoke_batch_>()(t, r);
    //! return t.get_aspect().template get<_invalid_request_>()(t, r);
  }
};

struct ad_invoke_exec
{
  template<typename T, typename R>
  R operator()(T& t, R r)
  {
    typedef typename T::aspect::template advice_cast<_deserializer_>::type deserializer;
    deserializer deser;
    
    r = deser.get_aspect().template get< parse::_space_ >()(deser, r);
    for(;r;)
    {
      r = t.get_aspect().template get<_invoke_>()( t, r );
      r = deser.get_aspect().template get< parse::_space_ >()(deser, r);
    }
    
    return r;
  }
};

}}}

#endif
