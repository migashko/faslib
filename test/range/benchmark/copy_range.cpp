#include <fas/range.hpp>
#include <fas/xtime.hpp>
#include <cstring>
#include <iostream>
#include <iterator>
#include <vector>

using namespace fas;

#define LIMIT_OP 100000000

const char str[]=
  "0123456789ABCDEF"
  "0123456789ABCDEF"
  "0123456789ABCDEF"
  "0123456789ABCDEF"
  
  "0123456789ABCDEF"
  "0123456789ABCDEF"
  "0123456789ABCDEF"
  "0123456789ABCDEF";
  
char res[sizeof(str)];

int main()
{
  const char** strpp = new const char*[LIMIT_OP];

  for (int i = 0; i < LIMIT_OP; ++i)
    strpp[i] = str;
  
  nanospan start, finish;
  
  for (int j = 0 ; j < 3 ; ++j)
  {
    start = process_nanotime();
    for (int i = 0; i < LIMIT_OP; ++i)
      std::memcpy(res, strpp[i], sizeof(str) );
    finish = process_nanotime();
    std::cout << "memcpy(char*): " << finish - start << std::endl;

    start = process_nanotime();
    for (int i = 0; i < LIMIT_OP; ++i)
      std::strcpy(res, strpp[i]);
    finish = process_nanotime();
    std::cout << "strcpy(char*): " << finish - start << std::endl;
    
    const char* beg;
    const char* end;
    char *dst;
    start = process_nanotime();
    for (int i = 0; i < LIMIT_OP; ++i)
    {
      beg = strpp[i];
      end = strpp[i] + sizeof(str);
      dst = res;
      for ( ; beg!=end; ++beg, ++dst )
        *dst = *beg;
    }
    finish = process_nanotime();
    std::cout << "for(char*): " << finish - start << std::endl;

    start = process_nanotime();
    for (int i = 0; i < LIMIT_OP; ++i)
    {
      beg = strpp[i];
      end = strpp[i] + sizeof(str);
      dst = res;
      
      std::copy(beg, end, dst);
    }
    finish = process_nanotime();
    std::cout << "std::copy(char*): " << finish - start << std::endl;
    
    typedef std::vector<char> vector_type;
    vector_type vstr(str, str + sizeof(str) );
    vector_type vres( vstr.size() );
    vector_type::iterator bitr = vstr.begin();
    vector_type::iterator eitr = vstr.end();
    vector_type::iterator ditr = vres.begin();
    start = process_nanotime();
    for (int i = 0; i < LIMIT_OP; ++i)
      std::copy(bitr, eitr, ditr);
    finish = process_nanotime();
    std::cout << "std::copy(iterator): " << finish - start << std::endl;

    start = process_nanotime();
    for (int i = 0; i < LIMIT_OP; ++i)
    {
      bitr = vstr.begin();
      eitr = vstr.end();
      ditr = vres.begin();
      
      for ( ;bitr!=eitr;++bitr, ++ditr)
        *ditr = *bitr;
    }
    finish = process_nanotime();
    std::cout << "for(iterator): " << finish - start << std::endl;
    

    std::vector<char> vres1( vstr.size(), 'Z' );
    typedef random_access_range<std::vector<char>::iterator> range_type;
    range_type rbeg(vstr.begin(), vstr.end());
    range_type rend(vstr.end(), vstr.end());
    range_type rdst(vres1.begin(), vres1.end());
  
    start = process_nanotime();
    for (int i = 0; i < LIMIT_OP; ++i)
      std::copy(rbeg, rend, rdst);
    finish = process_nanotime();
  
    std::cout << "std::copy(range): " << finish - start << std::endl;
  
    start = process_nanotime();
    for (int i = 0; i < LIMIT_OP; ++i)
    {
      rbeg = range_type(vstr.begin(), vstr.end());
      rend = range_type(vstr.end(), vstr.end());
      rdst = range_type(vres1.begin(), vres1.end());
      for ( ;rbeg!=rend;++rbeg, ++rdst)
        *rdst = *rbeg;
    }
    finish = process_nanotime();
    std::cout << "for(range): " << finish - start << std::endl;
    std::cout << std::endl;
  }

  return 0;
}
