#include <iostream>
#include <fas/xtime.hpp>
#include <fas/system/system.hpp>
#include <fas/system/colorized.hpp>

using namespace fas;


void psleep(int millitm)
{
  millispan start = nanotime();
  while ( millispan( nanotime() - start ) < millispan(0, millitm)  );
}


int main()
{
  nanospan pstart = process_nanotime();
  millispan middle_span;
  for ( int i = 0; i < 10 ; ++i)
  {
    microspan start = nanotime();
    system::sleep(100);
    microspan finish = nanotime();
    std::cout << "interval " << microspan(finish - start) 
              << " sec, rate " << microspan(rate( finish - start)) << std::endl;
    if ( middle_span == 0)
      middle_span = finish - start;
    else
      middle_span = ( middle_span + finish - start ) / 2;

    /*
    start = process_nanotime();
    system::sleep(100);
    finish = process_nanotime();
    std::cout << "interval " << finish - start << " sec, rate " << rate( finish - start) << std::endl;
    if ( middle_process_span == 0)
      middle_process_span = finish - start;
    else
      middle_process_span = ( middle_process_span + finish - start ) / 2;
    */

  }
  
  std::cout << "-------------------" << std::endl;
  std::cout << bold << "middle interval " << green << middle_span << restore 
            << bold << ", middle rate " << red << rate(middle_span) << restore << std::endl;
  

  nanospan pfinish = process_nanotime();
  
  std::cout << "execution time " << pfinish - pstart << std::endl;

  pstart = process_nanotime();
  psleep(100);
  //system::sleep(100);
  pfinish = process_nanotime();
  std::cout << "execution time " << pfinish - pstart << std::endl;
  
  return 0;
}