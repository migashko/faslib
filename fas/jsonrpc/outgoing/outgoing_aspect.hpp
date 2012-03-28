#ifndef FAS_JSONRPC_OUTGOING_OUTGOING_ASPECT_HPP
#define FAS_JSONRPC_OUTGOING_OUTGOING_ASPECT_HPP

#include <fas/jsonrpc/outgoing/tags.hpp>
#include <fas/jsonrpc/outgoing/ad_send.hpp>
#include <fas/jsonrpc/outgoing/ad_send_error.hpp>
#include <fas/jsonrpc/outgoing/ad_send_failed.hpp>

#include <fas/jsonrpc/outgoing/types/serializer.hpp>

#include <fas/aop/aspect.hpp>
#include <fas/aop/advice.hpp>
#include <fas/aop/value_advice.hpp>
#include <fas/aop/definition.hpp>
#include <fas/aop/value_advice.hpp>
#include <fas/type_list/type_list_n.hpp>


namespace fas{ namespace jsonrpc{

struct outgoing_buffer: std::vector<char> {};
  
struct outgoing_list
 : type_list_n<
    advice<_send_, ad_send>,
    advice<_send_error_, ad_send_error>,
    advice<_send_failed_, ad_send_failed>,
    definition< _serializer_, outgoing_serializer >,
    value_advice< _buffer_, outgoing_buffer >
  >::type
{};


struct outgoing_aspect: ::fas::aspect< outgoing_list > { };

}}

#endif
