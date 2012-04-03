#include <fas/range.hpp>
#include <fas/xtime.hpp>
#include <cstring>
#include <iostream>
#include <iterator>
#include <vector>

using namespace fas;

#define LIMIT_OP 10000000

const char str[]=
  "0123456789ABCDEF"
  "0123456789ABCDEF"
  "0123456789ABCDEF"
  "0123456789ABCDEF"
  
  "0123456789ABCDEF"
  "0123456789ABCDEF"
  "0123456789ABCDEF"
  "0123456789ABCDEF";
  
inline long strlen1(const char* str)
{
  for ( register long i = 0; ; ++i )
    if ( str[i] == '\0') return i;
}


template<typename I>
inline long strlen2(I itr)
{
  for ( I beg = itr; ; ++beg )
    if ( *beg == '\0') 
      return beg - itr;
}

template<typename I>
inline long strlen3(I itr)
{
  for ( long i = 0; ; ++i, ++itr )
    if ( *itr == '\0') 
      return i;
}

void show(nanospan start, nanospan finish)
{
  std::cout << finish - start << std::endl;
  std::cout << LIMIT_OP*rate(finish - start) << std::endl;
 
}

int main()
{
  const char* strp[10] = {str,str,str,str,str,str,str,str,str,str };
  const char** strpp = new const char*[LIMIT_OP];
  for (int i = 0; i < LIMIT_OP; ++i)
    strpp[i] = str;
  std::cout << sizeof('z') << std::endl;
  nanospan start;
  nanospan finish;
  
  for (int j = 0 ; j < 3 ; ++j)
  {
    
  std::cout << "++++++++++++++++++++++++++++++++++" << std::endl;
  
  long summ = 0;
  start = process_nanotime();
  for (int i = 0; i < LIMIT_OP; ++i)
    summ += std::strlen(strp[i%10]);
  finish = process_nanotime();
  std::cout << summ << std::endl;
  show(start, finish);

  std::cout << "-------------" << std::endl;
  summ = 0;
  start = process_nanotime();
  for (int i = 0; i < LIMIT_OP; ++i)
    summ += strlen1(str);
  finish = process_nanotime();
  std::cout << summ << std::endl;
  show(start, finish);

  std::cout << "-------------" << std::endl;
  summ = 0;
  start = process_nanotime();
  for (int i = 0; i < LIMIT_OP; ++i)
    summ += strlen2(str);
  finish = process_nanotime();
  std::cout << summ << std::endl;
  show(start, finish);

  std::cout << "-------------" << std::endl;
  std::vector<char> vc(str, str + sizeof(str) );
  std::vector<char>::iterator itr = vc.begin();
  //std::random_access_iterator<char> itr(str);
  summ = 0;
  start = process_nanotime();
  for (int i = 0; i < LIMIT_OP; ++i)
    summ += strlen2(itr);
  finish = process_nanotime();
  std::cout << summ << std::endl;
  show(start, finish);

  std::cout << "------ ++ -------" << std::endl;
  typerange<const char*>::range r = range(str, str + sizeof(str));
  summ = 0;
  start = process_nanotime();
  for (int i = 0; i < LIMIT_OP; ++i)
    summ += strlen2(r);
  finish = process_nanotime();
  std::cout << summ << std::endl;
  show(start, finish);

  std::cout << "-------------" << std::endl;
  forward_range< const char* > fr ( str, str + sizeof(str) );
  summ = 0;
  start = process_nanotime();
  for (int i = 0; i < LIMIT_OP; ++i)
    summ += strlen3(fr);
  finish = process_nanotime();
  std::cout << summ << std::endl;
  show(start, finish);
  
  }

  return 0;
}
