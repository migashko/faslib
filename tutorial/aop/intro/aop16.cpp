#include <fas/aop.hpp>
#include <fas/aop/is_has_tag.hpp>
#include <fas/algorithm.hpp>
#include <fas/type_list.hpp>
#include <fas/static_check.hpp>
#include <fas/typemanip.hpp>
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
    std::cout << "find" << std::endl;
    typename T::iterator itr =  t.get_container().find(key);
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
  fas::type_advice<_value_,  w< std::pair< _1, _2 > > >,
  fas::type_advice<_compare_, w<  std::less< _1 > > >,
  fas::type_advice<_allocator_, w<  std::allocator< _1 > > >,
  fas::type_advice<_container_, w<  std::map< _1, _2, _3, _4 > > >,
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
    typename fas::unwrap< typename aspect::template advice_cast<_value_>::type  >::type,
    const key_type,
    mapped_type
  >::type value_type;

  typedef typename fas::apply<
    typename fas::unwrap< typename aspect::template advice_cast<_compare_>::type >::type,
    key_type
  >::type key_compare;

  typedef typename fas::apply<
    typename fas::unwrap< typename aspect::template advice_cast<_allocator_>::type >::type,
    key_type
  >::type allocator_type;

  typedef typename fas::apply<
    typename fas::unwrap< typename aspect::template advice_cast<_container_>::type >::type,
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
  typedef typename super::aspect::net_list net_list;
  typedef typename super::aspect::flat_list flat_list;
  typedef typename super::aspect::hierarchy_list hierarchy_list;
  enum { value = fas::count_if< common_list, fas::is_has_tag<_1,_container_> >::value };
  enum { net_value = fas::count_if< net_list, fas::is_has_tag<_1,_container_> >::value };
  enum { result = fas::static_check< value == 2 >::value };
  enum { result2 = fas::static_check< net_value == 2 >::value };

  enum { result3 = fas::static_check< fas::length<net_list>::value == 8 >::value };
  enum { result4 = fas::static_check< fas::length<common_list>::value == 8 >::value };
  enum { result5 = fas::static_check< fas::length<hierarchy_list>::value == 8 >::value };

  typedef fas::erase_if<
    /*tail< */_1 /*>*/,
    a< fas::is_has_tag< p<_1>, fas::tag_cast< fas::head< _1 > > > >
  > remove_from_tail;

  typedef typename fas::transform_tail_if<
    flat_list,
    remove_from_tail,
    fas::is_remove_advice<_1>
  >::type net_list2;

  enum { result6 = fas::static_check< fas::length<net_list2>::value == 8 >::value };

};


template<class Key, class Value, class A = fas::aspect<> >
class key_value_container
  : public key_value_container_helper<Key, Value, A>::super
  , public key_value_container_helper<Key, Value, A>::container
{
public:
  typedef typename key_value_container_helper<Key, Value, A>::container container;

  container& get_container() { return *this;}
  
  typename container::iterator find(const typename container::key_type& key)
  {
    return this->get_aspect().template get<_find_>()(*this, key);
  }
  
};

int main()
{
  typedef key_value_container<int, std::string> dict_type;
  typedef typename fas::lambda<
    fas::not_<
      fas::is_has_tag<
        fas::_1, 
        fas::tag_cast<
          fas::head<
            fas::a<
              fas::type_list<
              fas::remove_advice<_allocator_>, fas::type_list<
              fas::remove_advice<_compare_>, fas::type_list<
              fas::remove_advice<_value_>, fas::type_list<
              fas::remove_advice<_container_>, fas::type_list<
              fas::type_advice<_value_, std::pair< p<fas::_1>,  p<fas::_2>  > >, fas::type_list<
              fas::type_advice<_compare_, std::less<  p<fas::_1> > >, fas::type_list<
              fas::type_advice<_allocator_, std::allocator<  p<fas::_1> >  >, fas::type_list<
              fas::type_advice<_container_, std::map<  p<fas::_1> ,  p<fas::_2>,  p<fas::_3>,  p<fas::_4> > >, fas::type_list<
              fas::advice<_find_, ad_find>, fas::empty_list> > > > > > > > > 
            > 
          > 
        > 
      > 
    >
  >::apply<_container_>::type aaa;
  dict_type::mapped_type sss = "aaa";
  dict_type dict;
  dict[1] = "aaa";
  dict.find(1);
  
  return 0;
}
