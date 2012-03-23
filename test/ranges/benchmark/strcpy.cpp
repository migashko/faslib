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
  
char res[sizeof(str)];

inline void strcpy0(const char* beg, const char* end, char *dst)
{
  memcpy( dst, beg, end - beg);
}

inline void strcpy1(const char* beg, const char* end, char *dst)
{
  for ( ; beg!=end; ++beg, ++dst )
    *dst = *beg;
}

inline void strcpy2(const char* beg, const char* end, char *dst)
{
  std::copy(beg, end, dst);
}

template<typename Itr>
inline void strcpy3(Itr beg, Itr end, Itr dst)
{
  std::copy(beg, end, dst);
}

template<typename Itr>
inline void strcpy4(Itr beg, Itr end, Itr dst)
{
  for ( ;beg!=end;++beg, ++dst)
    *dst = *beg;
}

template<typename R>
inline void strcpy5(R src, R dst)
{
  for ( ;src; ++src, ++dst)
    *dst = *src;
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
  //const char* strp[10] = {str,str,str,str,str,str,str,str,str,str };
  const char** strpp = new const char*[LIMIT_OP];
  for (int i = 0; i < LIMIT_OP; ++i)
    strpp[i] = str;
  std::cout << sizeof('z') << std::endl;
  nanospan start;
  nanospan finish;
  
  for (int j = 0 ; j < 3 ; ++j)
  {
    
  std::cout << "++++++++++++++++++++++++++++++++++" << std::endl;

  std::cout << "array std::memcpy" << std::endl;
  start = process_nanotime();
  for (int i = 0; i < LIMIT_OP; ++i)
    std::memcpy(res, strpp[i], sizeof(str) );
  finish = process_nanotime();
  
  show(start, finish);

  std::cout << "array std::strcpy" << std::endl;
  //long summ = 0;
  start = process_nanotime();
  for (int i = 0; i < LIMIT_OP; ++i)
    std::strcpy(res, strpp[i]);
  finish = process_nanotime();
  //std::cout << summ << std::endl;
  show(start, finish);

  std::cout << "array copy by item" << std::endl;
  //summ = 0;
  start = process_nanotime();
  for (int i = 0; i < LIMIT_OP; ++i)
    strcpy1(strpp[i], strpp[i] + sizeof(str), res);
  finish = process_nanotime();
  show(start, finish);

  //std::cout << "-------------" << std::endl;
  //summ = 0;
  std::cout << "array std::copy" << std::endl;
  start = process_nanotime();
  for (int i = 0; i < LIMIT_OP; ++i)
    strcpy2(strpp[i], strpp[i] + sizeof(str), res);
  finish = process_nanotime();
  //std::cout << summ << std::endl;
  show(start, finish);

  std::cout << "-----std::copy iterator--------" << std::endl;
  typedef std::vector<char> vector_type;
  vector_type vstr(str, str + sizeof(str) );
  vector_type vres( vstr.size() );
  vector_type::iterator bitr = vstr.begin();
  vector_type::iterator eitr = vstr.end();
  vector_type::iterator ditr = vres.begin();
  start = process_nanotime();
  for (int i = 0; i < LIMIT_OP; ++i)
    strcpy3(bitr, eitr, ditr);
  finish = process_nanotime();
  show(start, finish);

  std::cout << "-----handed copy iterator--------" << std::endl;

  start = process_nanotime();
  for (int i = 0; i < LIMIT_OP; ++i)
    strcpy4(bitr, eitr, ditr);
  finish = process_nanotime();
  show(start, finish);

  std::vector<char> vres1( vstr.size(), 'Z' );
  
  
  typedef random_access_range<std::vector<char>::iterator> range_type;
  /*
  std::vector<range_type> rbeg(LIMIT_OP, range_type(vstr.begin(), vstr.end()));
  std::vector<range_type> rend(LIMIT_OP, range_type(vstr.end(), vstr.end()));
  std::vector<range_type> rdst(LIMIT_OP, range_type(vres1.begin(), vres1.end()));
  */

  range_type rbeg(vstr.begin(), vstr.end());
  range_type rend(vstr.end(), vstr.end());
  range_type rdst(vres1.begin(), vres1.end());
/*random_access_range<std::vector<char>::iterator> rend(vstr.end(), vstr.end());
  random_access_range<std::vector<char>::iterator> rdst(vres1.begin(), vres1.end());
  */
  //assert(rbeg[10]==range_type(vstr.begin(), vstr.end()));
  std::cout << "-----std::copy range--------" << std::endl;
  
  start = process_nanotime();
  for (int i = 0; i < LIMIT_OP; ++i)
    strcpy3( rbeg, rend, rdst);
  finish = process_nanotime();
  
  assert(vstr==vres1);
  show(start, finish);

  std::cout << "----- handed copy range as iterator --------" << std::endl;
  start = process_nanotime();
  for (int i = 0; i < LIMIT_OP; ++i)
    strcpy4( rbeg, rend, rdst);
  finish = process_nanotime();
  assert(vstr==vres1);
  show(start, finish);

  std::cout << "----- handed copy range --------" << std::endl;
  start = process_nanotime();
  for (int i = 0; i < LIMIT_OP; ++i)
    strcpy5( rbeg, rdst);
  finish = process_nanotime();
  assert(vstr==vres1);
  show(start, finish);

  /*
  std::cout << "------ ++ -------" << std::endl;
  range_traits<const char*>::type r = (str, str + sizeof(str));
  summ = 0;
  start = process_nanotime();
  for (int i = 0; i < LIMIT_OP; ++i)
    ;
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
  */
  
  }

  return 0;
}
