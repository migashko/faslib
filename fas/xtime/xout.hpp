//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_XTIME_XOUT_HPP
#define FAS_XTIME_XOUT_HPP

#include <ostream>
#include <fas/xtime/nanospan.hpp>

namespace fas
{

template<xsec_t i> struct x_width;
template<> struct x_width<FAS_NANOSEC> { enum {value = 9}; };
template<> struct x_width<FAS_MICROSEC>{ enum {value = 6}; };
template<> struct x_width<FAS_MILLISEC>{ enum {value = 3}; };

}


namespace std
{
  template<long I>
  ostream& operator << ( ostream& os, const ::fas::xspan<I>& s )
  {
    os << s.sec << ".";
    streamsize w = os.width( ::fas::x_width< ::fas::xspan<I>::xmax >::value );
    ostream::char_type f =  os.fill('0');
    os << s.xsec;
    os.width(w);
    os.fill(f);
    return os;
  }
}

#endif
