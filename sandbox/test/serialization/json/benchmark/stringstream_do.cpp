#include <fas/range.hpp>
#include <fas/xtime.hpp>

#include "benchmark.hpp"
#include <sstream>
#include <iostream>



int main()
{
  Person t;

  std::stringstream ss, sss;
  ss << "id=100 name=Name email=email@example.com";
  std::string id_pair, name_pair, email_pair;
  fas::nanospan start = fas::process_nanotime();
  for (size_t i = 0; i < TOTAL_OP; ++i)
  {
    ss.seekg(0);
    ss >> id_pair >> name_pair >> name_pair;
    //sscanf(id_pair.c_str(), "id=%d", &t.id);
    /*t.id = std::atoi(id_pair.c_str() + id_pair.find('=') + 1 );
    t.name.assign(name_pair.begin() + name_pair.find('=') + 1, name_pair.end() );
    t.email.assign(email_pair.begin() + email_pair.find('=') + 1, email_pair.end() );
    */
  }
  fas::nanospan finish = fas::process_nanotime();
  std::cout << finish - start;
  std::clog << std::endl
            << t.id << std::endl
            << t.name << std::endl
            << t.email << std::endl;

  return 0;
}
