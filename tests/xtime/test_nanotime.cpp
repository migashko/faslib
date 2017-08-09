//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#include <iostream>
#include <cstdio>
#include <fas/xtime.hpp>
#include <fas/system/system.hpp>

using namespace fas;

#define MAX_I 10000000

int main()
{
  nanospan start = nanotime();
  if (start == nanospan(0) ) return 1;
  fas::system::sleep(100);
  nanospan finish = nanotime();
  if (finish == nanospan(0) ) return 2;
  if (finish == start) return 3;
  std::cout << start << std::endl;
  std::cout << finish << std::endl;

  start = process_nanotime();
  if (start == nanospan(0) ) return 4;
  fas::system::sleep(100);
  finish = process_nanotime();
  if (finish == nanospan(0) ) return 5;
  std::cout << start << std::endl;
  std::cout << finish << std::endl;
  if (finish == start) return 6;
  return 0;
}


