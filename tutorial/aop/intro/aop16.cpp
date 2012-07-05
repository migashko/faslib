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
struct _before_find_;
struct _find_;
struct _after_find_;

using fas::w;
using fas::a;
using fas::p;
using fas::_;
using fas::_1;
using fas::_2;
using fas::_3;
using fas::_4;

struct ad_find
{
  template<typename T>
  typename T::container_type::iterator operator()(T& t, const typename T::container_type::key_type& key)
  {
    //t.get_aspect().template getg<_before_find_>()( t, key );
    typename T::container_type::iterator itr =  t.container().find(key);
    typedef typename T::container_type::value_type value_type;
    //t.get_aspect().template getg<_after_find_>()( t, static_cast<value_type&>(*itr) );
    return itr;
  }

  template<typename T>
  typename T::container_type::const_iterator operator()(T& t, const typename T::container_type::key_type& key) const
  {
    //t.get_aspect().template getg<_before_find_>()( t, key );
    typename T::container_type::const_iterator itr =  t.get_container().find(key);
    typedef typename T::container_type::value_type value_type;
    //t.get_aspect().template getg<_after_find_>()( t, static_cast<const value_type&>(*itr) );
    return itr;
  }

};

typedef fas::aspect< fas::type_list_n<
  fas::type_advice<_compare_, w<  std::less< _ > > >,
  fas::type_advice<_allocator_, w<  std::allocator< _ > > >,
  fas::type_advice<_container_, w<  std::map< _, _, _, _> > >,
  fas::advice<_find_, ad_find>
>::type >  aspect_key_value_container;


template<class Key, class Value, class A = fas::aspect<> >
struct make_aspect
{
  typedef fas::aspect_class<
      A,
      aspect_key_value_container
  > original_aspect_class;
    
  typedef typename original_aspect_class::aspect original_aspect;

  typedef Key key_type;
  typedef Value mapped_type;

  typedef typename fas::apply<
    typename fas::unwrap< typename original_aspect::template advice_cast<_compare_>::type >::type,
    key_type
  >::type key_compare;

  typedef typename fas::apply<
    typename fas::unwrap< typename original_aspect::template advice_cast<_allocator_>::type >::type,
    key_type
  >::type allocator_type;

  typedef typename fas::apply<
    typename fas::unwrap< typename original_aspect::template advice_cast<_container_>::type >::type,
    key_type,
    mapped_type, 
    key_compare,
    allocator_type
  >::type container;

  typedef fas::aspect_class< fas::aspect< typename fas::type_list_n<
    fas::type_advice<_container_, container>,
    fas::remove_advice<_allocator_>,
    fas::remove_advice<_compare_>,
    fas::remove_advice<_value_>,
    fas::remove_advice<_container_>,
    A, 
    aspect_key_value_container
  >::type > > featured_aspect_class;

  typedef fas::aspect< typename featured_aspect_class::aspect::common_list > type;
 
};


template<class Key, class Value, class A = typename make_aspect<Key, Value, fas::aspect<> >::type >
class key_value_container
  : public fas::aspect_class< typename make_aspect<Key, Value, fas::aspect<> >::type >
  , public fas::aspect_class< typename make_aspect<Key, Value, fas::aspect<> >::type >::aspect::template advice_cast<_container_>::type
{
public:
  /*typedef typename key_value_container_helper<Key, Value, A>::super super;
  super _super;
  typename super::aspect& get_aspect() { return _super.get_aspect();}
  const typename super::aspect& get_aspect() const { return _super.get_aspect();}
  */
  
  // typedef typename key_value_container_helper<Key, Value, A>::container container_type;
  typedef typename fas::aspect_class< typename make_aspect<Key, Value, fas::aspect<> >::type >::aspect::template advice_cast<_container_>::type container_type;

  container_type& container() { return *this;}
  
  typename container_type::iterator find(const typename container_type::key_type& key)
  {
    return this->get_aspect().template get<_find_>()(*this, key);
  }
  
};

int main()
{
  typedef key_value_container<int, std::string > dict_type;
  dict_type dict;
  dict[1] = "10";
  
  typedef fas::type_advice<_container_, w< std::multimap<_,_,_,_> > > multimap_advice;

  typedef key_value_container<int, std::string, make_aspect< int, std::string, fas::aspect< fas::type_list_n<multimap_advice>::type> >::type > multidict_type;
  multidict_type multidict;
  std::cout << multidict.find(1)->second << std::endl;;
  multidict.container() = dict.container();
  multidict[1] = std::string("10");
  
  /*
  typedef fas::value_advice<_find_, int > va;
  typedef fas::type_list_n< va,  fas::aspect<>, fas::aspect<ta>  >::type ll;
  typedef fas::aspect_class< fas::aspect<ll> > sh;
  sh s;
  fas::field<va>::get( s.get_aspect() ).get_advice() = 10;
  s.get_aspect().get<_find_>() = 20;
  */
  
  return 0;
}
