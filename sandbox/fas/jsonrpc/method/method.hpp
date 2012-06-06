#ifndef FAS_JSONRPC_METHOD_METHOD_HPP
#define FAS_JSONRPC_METHOD_METHOD_HPP

#include <fas/jsonrpc/tags.hpp>
#include <fas/jsonrpc/method/method_base.hpp>
#include <fas/jsonrpc/method/method_aspect.hpp>


#include <stdexcept>

namespace fas{ namespace jsonrpc{


template<typename A = ::fas::aspect<> >
class method:
  public method_base<A, method_aspect>
{
  typedef method_base<A, method_aspect> super;
};

}}

#endif
