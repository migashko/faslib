#ifndef FAS_RPC_JSON_METHOD_HPP
#define FAS_RPC_JSON_METHOD_HPP

#include <fas/rpc/json/method_base.hpp>
#include <fas/rpc/json/method/aspect.hpp>

namespace fas{ namespace rpc{ namespace json{

template<typename A = ::fas::aspect<> >
class method
  : public method_base< A, method_aspect >
{
public:
  typedef method_base< A, method_aspect > super;
  typedef typename super::aspect aspect;
};
  
}}}

#endif
