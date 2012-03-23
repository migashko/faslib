#include <iostream>
#include <cstdio>
#include <fas/xtime.hpp>
#include <fas/system/system.hpp>


using namespace fas;

#define MAX_I 10000000

int main()
{
  //char buff[255];
  //const char* hello =  "hello";
  nanospan start = /*process_*/nanotime();
  
  //for (int x)
  /*for (int i = 0 ; i < 6; ++i)
    buff[i] = hello[i];*/
  //std::snprintf(buff, 255, "hello %d", 10);
  //time_t t = time(0);
//#warning nanospan работает намного медленнее чем microspan и millispan
  millispan x = 0;
  /*for (int i = 0 ; i < MAX_I; i++)
    x += i;*/
  fas::system::sleep(100);
  std::cout << x << std::endl;
  nanospan finish = /*process_*/nanotime();
  std::cout << x << std::endl;
  std::cout << "start: " << start << std::endl;
  std::cout << "finish: " << finish << std::endl;
  nanospan interval = finish - start;
  std::cout << "interval: " << interval << " sec" << std::endl;
  std::cout << "interval/2: " << interval/2 << " sec" << std::endl;
  std::cout << "rate: " << rate( interval )/**MAX_I*/  << " persec" << std::endl;
  std::cout << "1/interval: " << 1/interval<< " persec" << std::endl;
  std::cout << "rerate: " << rate( rate( interval))  << " persec" << std::endl;
  double rate2 = double(FAS_NANOSEC) / ( interval.sec * FAS_NANOSEC + interval.xsec ) ;
  std::cout << "rate2: " << rate2  << " persec" << std::endl;
  std::cout << "4/2: " << nanospan(4, 0) / nanospan(2,0)  << " sec" << std::endl;
  std::cout << "4/2: " << nanospan(4, 0) / nanospan(2L)  << " sec" << std::endl;
  std::cout << "4/2.5: " << nanospan(4, 0) / nanospan(2,500000)  << " sec" << std::endl;
  std::cout << "4/2.5: " << nanospan(4, 0) / nanospan(2.5)  << " sec" << std::endl;
  std::cout << LLONG_MAX << std::endl;
  
  return 0;
}


