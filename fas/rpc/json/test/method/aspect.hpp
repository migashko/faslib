#ifndef FAS_RPC_JSON_METHOD_TEST_ASPECT_HPP
#define FAS_RPC_JSON_METHOD_TEST_ASPECT_HPP

#include <fas/rpc/json/tags.hpp>
#include <fas/aop/aspect.hpp>
#include <fas/adv/ad_container_manager.hpp>
#include <fas/type_list/type_list_n.hpp>

#include <string>


#include <fas/rpc/json/error_code.hpp>
#include <fas/rpc/json/error_code_json.hpp>
#include <fas/rpc/json/error.hpp>
#include <fas/rpc/json/error_json.hpp>

#include <fas/serialization/json/ser/serializer.hpp>
#include <fas/serialization/json/deser/deserializer.hpp>


namespace fas{ namespace rpc{ namespace json{ namespace test{ 

struct _result_buffer_;
struct _result_buffer_manager_;

struct ad_error_moke
{
  template<typename T, typename TM, typename R>
  void operator() ( T& t, TM& tm, R params, error_code::type code, int id = 0 )
  {
    tm.get_aspect().template get<_serializer_>()
    (
      error_code_json(),
      static_cast<int>(code),
      tm.get_aspect().template get<_result_buffer_manager_>().initial_range(t)
    );
  }

  template<typename T, typename TM, typename R>
  void operator() ( T& t, TM& tm, R params, const error& err, int id  = 0 )
  {
    tm.get_aspect().template get<_serializer_>()
    (
      error_json(),
      err,
      tm.get_aspect().template get<_result_buffer_manager_>().initial_range(t)
    );
  }

};
  
typedef type_list_n<
  advice<_result_buffer_, std::string >,
  advice<_result_buffer_manager_, ad_container_manager<_result_buffer_> >,
  advice<_error_, ad_error_moke>,
  
  advice<_serializer_, ::fas::json::ser::serializer<> >,
  advice<_deserializer_, ::fas::json::deser::deserializer<> >,
  
  group<_clear_, type_list_n<_result_buffer_manager_>::type >,
  group<_dispose_, _result_buffer_manager_>,
  group<_initialize_, _result_buffer_manager_>
>::type method_advice_list;

typedef aspect< method_advice_list > method_aspect_type;

struct method_aspect: method_aspect_type { };
  
}}}}

#endif
