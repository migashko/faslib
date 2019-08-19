//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2018
//
// Copyright: See COPYING file that comes with this distribution
//

#include <fas/utility/ignore_args.hpp>
#include <fas/utility/useless_cast.hpp>

int main(int argc, const char* argv[])
{
  fas::ignore_arg(argc);
  fas::ignore_args(argc, argv);
  int a = 0;
  int b = 0;
  long c = 0;
  a = fas::useless_cast<int>(b);
  b = fas::useless_cast<int>(a);
  fas::ignore_args(a, b, c);
  return 0;
}
