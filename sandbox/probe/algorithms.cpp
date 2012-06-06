#include <fas/type_list.hpp>
// #include <fas/type_list_n.hpp>
#include <fas/type_traits.hpp>
#include <fas/utility.hpp>


typedef fas::type_list_n< fas::int2type<1>, fas::int2type<2>, fas::int2type<3>, fas::int2type<4>  >::type type_list;


template<typename L, template<typename> class P >
struct algo
{
  enum { value = P< typename L::left_type>::value};
};

template< template<typename> class F, template<int> class V >
struct turn_value
{
  template<typename T>
  struct apply : V< F<T>::value >
  {
  };
};


// fas::vbind1st< 3, fas::less>::template type  - формирует шаблон с одним параметром int
// fas::value2value< T >::template type
// fas::turn_value< template<typename> class P, template<int> class P >
int main()
{

  typedef algo<
      type_list,
      turn_value<
          fas::value2value,
          fas::vbind1st< 3, fas::less_temp>::apply
      >::apply
  > my_algo;

  return 0;
};
