                                                                                                                                                                                                                                                                #include "chain.hpp"
#include "chain_b.hpp"
#include "chain_c.hpp"
#include <fas/aop/aspect_merge.hpp>
//#include <sys/time.h>
#include <fas/system/system.hpp>
#include <fas/xtime.hpp>
#include <iostream>
#include <ios>
#include <iomanip>

//#define MAX_COUNT 10000000
#define MAX_COUNT 100000

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
  chain< fas::aspect_merge<aspect, fas::aspect_merge<chain_c::aspect, chain_b::aspect>::type >::type > c;

  for (int k = 0; k < 10 ; k++)
  {
    /*
    timeval start1, finish1, start2, finish2;
    ::gettimeofday(&start1, 0);
    */
    fas::nanospan start1 = fas::nanotime();
    for (int i=0; i < MAX_COUNT; i++)
      //for (int j=0; j < MAX_COUNT; j++)
      c.method1(i);
    //::gettimeofday(&finish1, 0);
    fas::nanospan finish1 = fas::nanotime();

    // ::gettimeofday(&start2, 0);
    fas::nanospan start2 = fas::nanotime();
    for (int i=0; i < MAX_COUNT; i++)
      c.methodn(i);
    fas::nanospan finish2 = fas::nanotime();
    
    //::gettimeofday(&finish2, 0);

    std::cout << finish1 - start1 << std::endl;
    std::cout << finish2 - start2 << std::endl;

    /*showtime(start1, finish1);
    showtime(start2, finish2);
    */
    std::cout << "----------------------------" << std::endl;
  }

  std::cout << c.get_aspect().get<chain_a::_chain1_>().v << std::endl;
  std::cout << c.get_aspect().get<chain_a::_chain2_>().v << std::endl;
  std::cout << c.get_aspect().get<chain_a::_chain3_>().v << std::endl;
  std::cout << c.get_aspect().get<chain_a::_chain4_>().v << std::endl;
  std::cout << c.get_aspect().get<chain_a::_chain5_>().v << std::endl;
  std::cout << c.get_aspect().get<chain_a::_chain6_>().v << std::endl;
  std::cout << c.get_aspect().get<chain_b::_chain1_>().v << std::endl;
  std::cout << c.get_aspect().get<chain_b::_chain2_>().v << std::endl;
  std::cout << c.get_aspect().get<chain_b::_chain3_>().v << std::endl;
  std::cout << c.get_aspect().get<chain_b::_chain4_>().v << std::endl;
  std::cout << c.get_aspect().get<chain_b::_chain5_>().v << std::endl;
  std::cout << c.get_aspect().get<chain_b::_chain6_>().v << std::endl;
  std::cout << c.get_aspect().get<chain_c::_chain1_>().v << std::endl;
  std::cout << c.get_aspect().get<chain_c::_chain2_>().v << std::endl;
  std::cout << c.get_aspect().get<chain_c::_chain3_>().v << std::endl;
  std::cout << c.get_aspect().get<chain_c::_chain4_>().v << std::endl;
  std::cout << c.get_aspect().get<chain_c::_chain5_>().v << std::endl;
  std::cout << c.get_aspect().get<chain_c::_chain6_>().v << std::endl;
  
  return 0;
};
