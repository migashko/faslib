#ifndef FAS_JSONRPC_OUTGOING_OUTGOING_ASPECT_TYPE_HPP
#define FAS_JSONRPC_OUTGOING_OUTGOING_ASPECT_TYPE_HPP

#include <fas/jsonrpc/outgoing/tags.hpp>
#include <fas/jsonrpc/outgoing/ad_send.hpp>

#include <fas/aop/aspect.hpp>
#include <fas/aop/advice.hpp>
//#include <fas/aop/value_advice.hpp>

#include <fas/type_list/type_list_n.hpp>


struct buffer_vector: std::vector<char> {};

namespace fas{ namespace jsonrpc{

typedef type_list_n<
  advice<_send_, ad_send>,
  value_advice< _buffer_, buffer_vector >
>::type outgoing_advice_list;

typedef ::fas::aspect< outgoing_advice_list > outgoing_aspect_type;

}}

#endif
