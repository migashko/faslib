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
  if (start == 0) return 1;
  fas::system::sleep(100);
  nanospan finish = nanotime();
  if (finish == 0) return 1;
  if (finish == start) return 1;

  start = process_nanotime();
  if (start == 0) return 1;
  fas::system::sleep(100);
  finish = process_nanotime();
  if (finish == 0) return 1;
  if (finish == start) return 1;
  return 0;
}


