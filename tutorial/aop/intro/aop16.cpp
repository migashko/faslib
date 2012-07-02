#include <fas/aop.hpp>
#include <fas/type_list.hpp>
#include <map>
#include <string>
#include <iostream>

struct _key_;
struct _mapped_;
struct _value_;
struct _compare_;
struct _allocator_;
struct _container_;
struct _find_;

using fas::w;
using fas::a;
using fas::p;
using fas::_1;
using fas::_2;
using fas::_3;
using fas::_4;

struct ad_find
{
  template<typename T>
  typename T::iterator operator()(T& t, const typename T::key_type& key)
  {
    typename T::iterator itr =  t.find(key);
    return itr;
  }
};

/*struct aspect_key_value_container: fas::aspect< fas::type_list_n<
  fas::type_advice<_value_, a< std::pair<_1, _2> > >,
  fas::type_advice<_compare_, a< std::less<_1> > >,
  fas::type_advice<_allocator_, a< std::allocator<_1> > >,
  fas::type_advice<_container_, a< std::map<_1, _2, _3, _4> > >,
  fas::advice<_find_, ad_find>
>::type > {};
*/

typedef fas::aspect< fas::type_list_n<
  fas::type_advice<_value_, a< std::pair<_1, _2> > >,
  fas::type_advice<_compare_, a< std::less<_1> > >,
  fas::type_advice<_allocator_, a< std::allocator<_1> > >,
  fas::type_advice<_container_, a< std::map<_1, _2, _3, _4> > >,
  fas::advice<_find_, ad_find>
>::type >  aspect_key_value_container;


template<class Key, class Value, class A>
struct key_value_container_helper
{
  typedef 
    fas::aspect_class< 
      A,
      /*fas::aspect< typename fas::type_list_n<
        fas::type_advice<_key_, Key>,
        fas::type_advice<_mapped_, Value>
      >::type >,*/
      aspect_key_value_container
    > aspect_class;
    
  typedef typename aspect_class::aspect aspect;

  /*typedef typename aspect_class::aspect::template advice_cast<_key_>::type key_type;
  typedef typename aspect_class::aspect::template advice_cast<_mapped_>::type mapped_type;
  */
  typedef Key key_type;
  typedef Value mapped_type;

  typedef typename fas::apply<
    typename aspect::template advice_cast<_value_>::type,
    const key_type,
    mapped_type
  >::type value_type;

  typedef typename fas::apply<
    typename aspect::template advice_cast<_compare_>::type,
    key_type
  >::type key_compare;

  typedef typename fas::apply<
    typename aspect::template advice_cast<_allocator_>::type,
    key_type
  >::type allocator_type;

  typedef typename fas::apply<
    typename aspect::template advice_cast<_container_>::type,
    key_type,
    mapped_type, 
    key_compare,
    allocator_type
  >::type container;

  typedef fas::aspect_class< fas::aspect< typename fas::type_list_n<
    /*fas::remove_advice<_allocator_>,
    fas::remove_advice<_compare_>,
    fas::remove_advice<_value_>,
    fas::remove_advice<_container_>,*/
    fas::type_advice<_value_, value_type >,
    fas::type_advice<_compare_, key_compare >,
    fas::type_advice<_allocator_, allocator_type >,
    fas::remove_advice<_allocator_>,
    fas::remove_advice<_compare_>,
    fas::remove_advice<_value_>,
    fas::remove_advice<_container_>,
    A, 
    aspect_key_value_container
  >::type > > super;
  
  typedef typename super::aspect::common_list common_list;
  
};


template<class Key, class Value, class A = fas::aspect<> >
class key_value_container
  : public key_value_container_helper<Key, Value, A>::super
  , public key_value_container_helper<Key, Value, A>::container
{
public:
  typedef typename key_value_container_helper<Key, Value, A>::container container;
  
  typename container::iterator find(const typename container::key_type& key)
  {
    return this->get_aspect().template get<_find_>()(*this, key);
  }
  
};

int main()
{
  typedef key_value_container<int, std::string> dict_type;
  
  
  /*dict_type::mapped_type sss = "aaa";
  dict_type dict;
  dict[1] = "aaa";
  dict.find(1);
  */
  return 0;
}
