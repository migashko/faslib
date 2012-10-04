//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#include <iostream>
#include <cstdio>
#include <fas/xtime/nanospan.hpp>
#include <fas/xtime/microspan.hpp>
#include <fas/xtime/millispan.hpp>
#include <fas/xtime/xop.hpp>
#include <fas/xtime/xout.hpp>

using namespace fas;

template<typename X>
bool test_xspan()
{
  std::cout << 20 << std::endl;

  X span;
  
  if ( span.sec!=0 || span.xsec!=0 )  return false;
  
  span = X(10, 1);
  
  if ( span.sec!=10 || span.xsec!=1 )  return false;
  
  /// ----------------
  
  span = span + 1;
  span += -2;
  span += 2;
  
  if ( span.sec!=11 || span.xsec!=1 )  return false;
  
  span = span + X(10, X::xmax/2 - 1);
  
  if ( span.sec!=21 || span.xsec!=X::xmax/2)  return false;
  
  span = span + X(0, X::xmax/2 + 1);
  
  if ( span.sec!=22 || span.xsec!=1)  return false;
  
  span += X(0, X::xmax - 1);
  
  if ( span.sec!=23 || span.xsec!=0)  return false;
  
  span += nanospan(0, nanospan::xmax/2);
  
  if ( span.sec!=23 || span.xsec!=X::xmax/2)  return false;
  std::cout << 53 << " " << span.sec << " "<< span.xsec << ":" << microspan::xmax << std::endl;
    std::cout << "span.sec " << span.sec << std::endl;
  std::cout << "span.xsec " << span.xsec << std::endl;
  std::cout << "millispan::xmax " << millispan::xmax << std::endl;
  std::cout << "millispan::xmax/2 " << millispan::xmax/2 << std::endl;
 span += microspan(0, microspan::xmax/2); 
  std::cout << 55 << " " << span.sec << " "<< span.xsec << ":" << microspan::xmax << std::endl;
    std::cout << "span.sec " << span.sec << std::endl;
  std::cout << "span.xsec " << span.xsec << std::endl;
if ( span.sec!=24 || span.xsec!=0)  return false;

  span += millispan(0, millispan::xmax/2);
    std::cout << 59 << std::endl;
  if ( span.sec!=24 || span.xsec!=X::xmax/2)  return false;
  
  /// ---------------- 
  
  span = span - 1;
  span -= -2;
  span -= 2;
  std::cout << 67 << std::endl;  
  if ( span.sec!=23 || span.xsec!=X::xmax/2)  return false;
  
  span = span - X(10, X::xmax/2 + 1);
  std::cout << 71 << std::endl;
  if ( span.sec!=12 || span.xsec!=X::xmax - 1)  return false;
  
  span -= X(0, X::xmax - 1);
  std::cout << 75 << std::endl;
  if ( span.sec!=12 || span.xsec!=0)  return false;
  
  span -= nanospan(0, nanospan::xmax/2);
  std::cout << 79 << std::endl;
  if ( span.sec!=11 || span.xsec!=X::xmax/2)  return false;
  
  span -= microspan(0, microspan::xmax/2);
    std::cout << 83 << std::endl;
  std::cout << 84 << std::endl;
  if ( span.sec!=11 || span.xsec!=0)  return false;

  span -= millispan(0, millispan::xmax/2);
  std::cout << 88 << std::endl;
  if ( span.sec!=10 || span.xsec!=X::xmax/2)  return false;
  
  /// ---------------- 
  
  span = span / 2;
  
  if ( span.sec!=5 || span.xsec!=X::xmax/4)  return false;

  span /= 0.25;

  if ( span.sec!=21 || span.xsec!=0)  return false;
  
  span = ( span + 4 ) / 5;
  
  if ( span.sec!=5 || span.xsec!=0)  return false;
  
  /// ----------------
  
  span = span * 5;
  if ( span.sec!=25 || span.xsec!=0)  return false;
  
  span *= 0.2;
  if ( span.sec!=5 || span.xsec!=0)  return false;
  
  span *= X(1, X::xmax/10);
  if ( span.sec!=5 || span.xsec!=X::xmax*5/10)  return false;
  
  span *= 1.1;
  if ( span.sec!=6 || span.xsec!=X::xmax*5/100)  return false;

  // сравнение 
  if ( span == X() ) return false;
  if ( span == 0 ) return false;
  if ( span == 0.0 ) return false;

  if ( X() != X(0, 0) ) return false;
  if ( X() != 0 ) return false;
  if ( X() != 0.0 ) return false;
  
  span = 1.5;
  
  if ( span > 1.5) return false;
  if ( span >= 1.51) return false;
  if ( span < 1.5) return false;
  if ( span != 1.5) return false;
  if ( !(span == 1.5)) return false;
  if ( !(span >= 1.5)) return false;
  if ( !(span <= 1.5)) return false;
  
  if ( span != X(1, X::xmax/2) ) return false;
  
  return true;
}

int main()
{
  std::cout << 0 << std::endl;
  if ( !test_xspan<nanospan>() )
    return -1;
  std::cout << 1 << std::endl;
  if ( !test_xspan<microspan>() )
    return -1;
  std::cout << 2 << std::endl;
  if ( !test_xspan<millispan>() )
    return -1;
  std::cout << 3 << std::endl;
  return 0;
}


