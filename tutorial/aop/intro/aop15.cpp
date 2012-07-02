#include <fas/aop.hpp>
#include <fas/type_list.hpp>
#include <iostream>

template<int V1, int V2, typename TgNext>
struct ad_cell
{
  template<typename T>
  void operator()(T& t, int value)
  {
    std::cout<< "chain-" << V1 << "." << V2 << "(" << value << ")->" ;
    t.get_aspect().template get<TgNext>()(t, ++value);
  }
};

namespace chain1{
  
struct _input_;
struct _output_;
struct _incoming_;
struct _outgoing_;

struct _cell1_;
struct _cell2_;
struct _cell3_;
struct _cell4_;
struct _cell5_;
struct _cell6_;

struct aspect_chain1: fas::aspect< fas::type_list_n<
  fas::advice< _cell1_, ad_cell<1, 1, _cell2_>    >,
  fas::advice< _cell2_, ad_cell<1, 2, _cell3_>    >,
  fas::advice< _cell3_, ad_cell<1, 3, _outgoing_> >,
  fas::advice< _cell4_, ad_cell<1, 4, _cell5_>    >,
  fas::advice< _cell5_, ad_cell<1, 5, _cell6_>    >,
  fas::advice< _cell6_, ad_cell<1, 6, _output_>   >,
  fas::alias<_input_, _cell1_>,
  fas::alias<_incoming_, _cell4_>,
  fas::alias<_outgoing_, _cell4_>,
  fas::stub<_output_>
>::type > {};

  
} // namespace chain1

struct _input_;
struct _output_;

struct ad_final_chain
{
  template<typename T>
  void operator()(T& t, int value)
  {
    std::cout << "Done(" << value << ")!" << std::endl;
  }
};


struct ichain
{
  virtual ~ichain() {}
  virtual void run(int value) = 0;
};

struct aspect_chain: fas::aspect< fas::type_list_n<
  fas::alias<_input_, _output_>,
  fas::advice< _output_, ad_final_chain>
>::type > {};

template< typename A = fas::aspect<> >
class chain_base
  : public fas::aspect_class< A, aspect_chain >
  , public ichain
{
protected:
  template<typename T>
  void _run( T& t, int value)
  {
    t.get_aspect().template get<_input_>()( t, value);
  }
};

template< typename A = fas::aspect<> >
class chain:
  public chain_base<A>
{
public:
  virtual void run(int value)
  {
    chain_base<A>::_run(*this, value);
  }
};

struct aspect_chain1: fas::aspect< fas::type_list_n<
  fas::alias<_input_, chain1::_input_>,
  fas::alias<chain1::_output_, _output_>,
  chain1::aspect_chain1,
  aspect_chain
>::type > {};

int main()
{
  ichain* cc[2] = {
    new chain<>(),
    // new chain<chain1::aspect_chain1>()
    new chain<aspect_chain1>()
  };
  for (int i = 0; i < 2 ; ++i)
  {
    cc[i]->run( 1 );
    delete cc[i];
  }
  return 0;
}
