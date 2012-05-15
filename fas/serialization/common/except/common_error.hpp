//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2012
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_SERIALIZATION_COMMON_EXCEPT_COMMON_ERROR_HPP
#define FAS_SERIALIZATION_COMMON_EXCEPT_COMMON_ERROR_HPP

#include <fas/range/distance.hpp>
#include <fas/range/advance.hpp>
#include <fas/range/begin.hpp>
#include <fas/range/end.hpp>

#include <string>
#include <stdexcept>
#include <cstddef>

namespace fas{ namespace serialization{

class common_error
  : public std::runtime_error
{

public:
  typedef std::ptrdiff_t size_type;

  common_error(const std::string& msg, size_type tail_of = 0 )
    : std::runtime_error(msg)
    , _tail_of(tail_of)
  { }

  size_type tail_of() const { return _tail_of; }

  template<typename R>
  std::string message( R r ) const
  {
    if ( ::fas::distance(r) < _tail_of )
      return this->what();

    std::string msg;
    msg = this->what();

    R rr = r;
    ::fas::advance(rr, ::fas::distance(r) - _tail_of );

    msg += std::string(": ") 
        + std::string( ::fas::begin(r), ::fas::begin(rr) ) 
        + ">>>" 
        + std::string( ::fas::begin(rr), ::fas::end(r) );
    return msg;
  };

private:
  std::ptrdiff_t _tail_of;
};

}}

#endif
