#include "chain.hpp"
#include "chain_b.hpp"
#include "chain_c.hpp"
#include <fas/aop/aspect_merge.hpp>
// #include <sys/time.h>
#include <iostream>
#include <ios>
#include <iomanip>
#include <fas/system/system.hpp>
#include <fas/xtime.hpp>

//#define MAX_COUNT 10000000
#define MAX_COUNT 100000

/*
struct aspect: fas::aspect<
  fas::type_list_n<
    fas::alias<chain_a::_incoming_, chain_b::_input_>,
    fas::alias<chain_b::_output_, chain_a::_outgoing_>,

    fas::alias<chain_b::_incoming_, chain_c::_input_>,
    fas::alias<chain_c::_output_, chain_b::_outgoing_>,

    fas::alias<chain_c::_incoming_, chain_c::_outgoing_ >
  >::type
>
{};
*/
/*
void showtime( timeval start1, timeval finish1 )
{
  time_t secspan = finish1.tv_sec - start1.tv_sec;
  time_t usecspan = 0;
  if ( finish1.tv_usec < start1.tv_usec )
  {
    secspan-=1;
    usecspan = 1000000 + finish1.tv_usec - start1.tv_usec ;
  }
  else
    usecspan = finish1.tv_usec - start1.tv_usec;
  std::cout << secspan << "." << std::setw(6) << std::setfill('0') << usecspan << std::endl;
};
*/

int main()
{
  //chain< fas::aspect_merge<aspect, fas::aspect_merge<chain_c::aspect, chain_b::aspect>::type >::type > c;
  ad_chain<'A', 1, void> a1;
  ad_chain<'A', 2, void> a2; a1.next = &a2;
  ad_chain<'A', 3, void> a3; a2.next = &a3;
  ad_chain<'B', 1, void> b1; a3.next = &b1;
  ad_chain<'B', 2, void> b2; b1.next = &b2;
  ad_chain<'B', 3, void> b3; b2.next = &b3;
  ad_chain<'C', 1, void> c1; b3.next = &c1;
  ad_chain<'C', 2, void> c2; c1.next = &c2;
  ad_chain<'C', 3, void> c3; c2.next = &c3;
  ad_chain<'C', 4, void> c4; c3.next = &c4;
  ad_chain<'C', 5, void> c5; c4.next = &c5;
  ad_chain<'C', 6, void> c6; c5.next = &c6;
  ad_chain<'B', 4, void> b4; c6.next = &b4;
  ad_chain<'B', 5, void> b5; b4.next = &b5;
  ad_chain<'B', 6, void> b6; b5.next = &b6;
  ad_chain<'A', 4, void> a4; b6.next = &a4;
  ad_chain<'A', 5, void> a5; a4.next = &a5;
  ad_chain<'A', 6, void> a6; a5.next = &a6;

  for (int k = 0; k < 10 ; k++)
  {
    //timeval start1, finish1, start2, finish2;

    //::gettimeofday(&start1, 0);
    fas::nanospan start1 = fas::nanotime();
    for (int i=0; i < MAX_COUNT; i++)
      a1.vmethod1(i);
    fas::nanospan finish1 = fas::nanotime();
    //::gettimeofday(&finish1, 0);

    //::gettimeofday(&start2, 0);
    fas::nanospan start2 = fas::nanotime();
    for (int i=0; i < MAX_COUNT; i++)
      a1.vmethodn(i);
    fas::nanospan finish2 = fas::nanotime();
    //::gettimeofday(&finish2, 0);

    std::cout << finish1 - start1 << std::endl;
    std::cout << finish2 - start2 << std::endl;
    /*showtime(start1, finish1);
    showtime(start2, finish2);
    */
    std::cout << "----------------------------" << std::endl;
    //std::cout << c.get_aspect().get<chain_a::_chain2_>().v << std::endl;
  }
  return 0;
};
