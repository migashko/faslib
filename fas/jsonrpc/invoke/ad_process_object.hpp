#include <fas/system/disable_warnings.hpp>

#ifndef FAS_JSONRPC_JSONRPC_HANDLER_HPP
#define FAS_JSONRPC_JSONRPC_HANDLER_HPP

#include <fas/jsonrpc/tags.hpp>
#include <fas/jsonrpc/aspect.hpp>
#include <fas/jsonrpc/raw_object.hpp>
#include <fas/jsonrpc/raw_object_json.hpp>

#include <fas/aop/aspect.hpp>
#include <fas/aop/advice.hpp>
#include <fas/type_list/type_list_n.hpp>

namespace fas{ namespace jsonrpc{
  
struct _result_buffer_;

struct _process_valid_;

struct _notifications_;

template<typename Obj>
struct f_notify
{
  const Obj& obj;
  volatile bool ready;
  
  f_notify(const Obj& obj)
    : obj(obj)
    , ready(false) 
  {}
  
  template<typename T, typename Tg>
  void operator()(T& t, tag<Tg> )
  {
    if (ready) return;

    if ( !t.get_aspect().template get<Tg>().check_name( obj.name_range() ) )
      return;
    
    ready = true;
   
    t.get_aspect().template get<Tg>().process_notify( t, obj.params_range() );
  }
  
  operator bool () const { return ready; }
};

template<typename Obj>
struct f_request
{
  const Obj& obj;
  volatile bool ready;
  
  f_request(const Obj& obj)
    : obj(obj)
    , ready(false) 
  {}
  
  template<typename T, typename Tg>
  void operator()(T& t, tag<Tg> )
  {
    if (ready) return;

    if ( !t.get_aspect().template get<Tg>().check_name( obj.name_range() ) )
      return;
    
    ready = true;
   
    t.get_aspect().template get<Tg>().process_request( t, obj.params_range(), obj.id );
  }
  
  operator bool () const { return ready; }
};


struct _search_notify_;
struct ad_search_notify
{
  template<typename T, typename Obj>
  void operator()(T& t, const Obj& obj )
  {
    if ( !t.get_aspect().template getg<_method_>().for_each(t, f_notify<Obj>( obj ) ) )
      t.get_aspect().template get<_method_not_found_>()(t);
  }
};

struct _search_request_;
struct ad_search_request
{
  template<typename T, typename Obj>
  void operator()(T& t, const Obj& obj )
  {
    if ( !t.get_aspect().template getg<_method_>().for_each(t, f_request<Obj>( obj ) ) )
      t.get_aspect().template get<_method_not_found_>()(t);
  }
};


struct ad_process_valid
{
  template<typename T, typename Obj>
  void operator()(T& t, const Obj& obj )
  {
    if ( obj.is_notify() )
    {
      t.get_aspect().template get<_search_notify_>()(t, obj);
    }
    else if ( obj.is_request() )
    {
      t.get_aspect().template get<_search_request_>()(t, obj);
    }
    else if ( obj.is_result() )
    {
      
    }
    else if ( obj.is_error() )
    {
      
    }
  }
};

struct ad_process_object
{
  template<typename T, typename R>
  R operator()(T& t, R r )
  {
    typedef typename T::aspect::template advice_cast<_deserializer_>::type deserializer;
    deserializer deser;
    
    raw_object obj;
    try
    {
      r = deser(raw_object_json(), obj, r);
    }
    catch( ::fas::json::json_error& e )
    {
      std::cout << "ad_invoke catch " << e.what() << std::endl;
      // если и здесь exception то прерываем 
      // Сделать разные стратегии десериализации (с отправкой доп. поля description )
      /*r = deser.get_aspect().template get< ::fas::json::parser::_value_>()(deser, r);
      t.get_aspect().template get<_invalid_request_>()(t );
      */
      typedef typename T::aspect::template advice_cast<_parser_>::type parser;
      
      parser p;
      r = p.parse_object(r);
      t.get_aspect().template get<_parse_error_>()(t);
      return r;
    }
    
    if ( obj.is_valid() )
    {
      std::cout << "ad_invoke valid" << std::endl;
      t.get_aspect().template get<_process_valid_>()(t, obj);
    }
    else if ( obj.has_id() )
    {
      // TODO: для range_object передаем отработанный интервал
      std::cout << "ad_invoke invalid has_id" << std::endl;
      t.get_aspect().template get<_invalid_request_>()(t, obj.id );
    }
    else
    {
      std::cout << "ad_invoke invalid not has_id" << std::endl;
      t.get_aspect().template get<_invalid_request_>()(t);
    }
    
    return r;
  }
};


/*
struct ad_process_object
{
  template<typename T, typename R>
  R operator()( T& t, R r)
  {
    try
    {
      return t.get_aspect().template get<_invoke_>()(t, r);
    }
    catch(const ::fas::json::json_error& e)
    {
      // TODO:
    }
    return r;
  }
};
*/

struct ad_process
{
  template<typename T, typename R>
  R operator()( T& t, R r)
  {
    // TODO: обертка с обработкой исключений всего диапазона 
    typedef typename T::aspect::template advice_cast<_parser_>::type parser;
    parser p;
    r = p.parse_space(r);
    while( r )
    {
      std::cout << std::endl << "ad_process" << std::endl;
      if ( p.is_object(r) )
      {
        r = t.get_aspect().template get<_process_object_>()(t, r);
      }
      else if ( p.is_array(r) )
      {
        r = p.parse_array(r);
      }
      else 
      {
        r = p.parse_value(r);
        t.get_aspect().template get<_invalid_request_>()(t);
      }
      r = p.parse_space(r);
    }
    return r;
  }
};

struct ad_moke_output
{
  template<typename T, typename R>
  void operator()(T& t, R r)
  {
    std::cout << "ad_moke_output" << std::endl;
    t.get_aspect().template get<_result_buffer_>().assign( r.begin(), r.end() );
  }
};

typedef type_list_n<
  //advice< _invoke_, ad_invoke>,
  advice< _process_, ad_process>,
  advice< _process_valid_, ad_process_valid>,
  advice< _search_notify_, ad_search_notify>,
  advice< _search_request_, ad_search_request>,
  advice< _process_object_, ad_process_object>,
  advice< _result_buffer_, std::string >,
  advice< _output_, ad_moke_output > 
>::type jsonrpc_handler_advice_list;

typedef ::fas::aspect< jsonrpc_handler_advice_list > jsonrpc_handler_aspect_type;

struct jsonrpc_handler_aspect: jsonrpc_handler_aspect_type { };

struct jsonrpc_aspect: aspect_merge< jsonrpc_handler_aspect, ::fas::jsonrpc::aspect >::type {};
  
template<typename A = ::fas::aspect<> >
class jsonrpc_handler
  : public aspect_class< A,  jsonrpc_aspect >
{
  typedef aspect_class< A, jsonrpc_aspect > super;
  
public:

  typedef typename super::aspect aspect;
  typedef typename aspect::template advice_cast<_result_buffer_>::type result_buffer;

  template<typename T, typename R>
  R operator()( T& t, R r)
  {
    return _process(t, r);
  }

  template<typename R>
  R operator()( R r)
  {
    return _process(*this, r);
  }

  result_buffer& result() { return super::get_aspect().template get<_result_buffer_>(); }
  
  const result_buffer& result() const { return super::get_aspect().template get<_result_buffer_>(); }
  
protected:
  
  template<typename T, typename R>
  R _process( T& t, R r)
  {
    return t.get_aspect().template get<_process_>()(t, r);
  }
};

}}

#endif
#include <fas/system/enable_warnings.hpp>
