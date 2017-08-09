//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013
//
// Copyright: See COPYING file that comes with this distribution
//

#include <fas/aop.hpp>
#include <fas/type_list.hpp>
#include <fas/mp.hpp>

#include <iostream>
#include <vector>

struct _value_;
struct _provider1_;
struct _provider2_;
struct _creator_;

template<typename T>
class provider
{
  typedef typename T::aspect::template advice_cast<_value_>::type value_type;
public:
  explicit provider(T* t)
  {
    _target = t;
  }

  void set(const value_type& value)
  {
    _target->get_aspect().template get<_value_>()=value;
  }

  const value_type& get() const
  {
    return _target->get_aspect().template get<_value_>();
  }


private:
  T* _target;
};

struct aspect: fas::aspect< fas::type_list_n<
  fas::provider< _provider1_, fas::w< provider< fas::_1 > > > ,
  fas::provider_t< _provider2_,  provider>,
  fas::creator< _creator_, std::vector<int>  > ,
  fas::value< _value_, int >
>::type >{};

template<typename A>
class test
  : public fas::aspect_class<A>
{
  typedef test<A> self;
  typedef fas::aspect_class<A> super;
public:
  typedef typename super::aspect::template advice_cast<_value_>::type value_type;
  typedef typename super::aspect::template advice_cast<_provider1_>::type::template apply< self >::type provider1_type;
  typedef typename super::aspect::template advice_cast<_provider2_>::type::template apply< self >::type provider2_type;
  typedef typename super::aspect::template advice_cast<_creator_>::type::template apply< self >::type creator_type;
  
  template<typename P1, typename P2>
  const creator_type& vector(P1 p1, P2 p2)
  {
    _container = super::get_aspect().template get<_creator_>()(*this, p1, p2);
    return _container;
  }

  void set(const value_type& val)
  {
    super::get_aspect().template get<_value_>() = val;
  }

  const value_type& get() const
  {
    return super::get_aspect().template get<_value_>();
  }

  provider1_type get_provider1()
  {
    return provider1_type(this);
  }

  provider2_type get_provider2()
  {
    return provider2_type(this);
  }
private:
  creator_type _container;
};

int main()
{
  test<aspect> t;
  test<aspect>::provider1_type p = t.get_provider2();
  p = t.get_provider1();
  t.set(10);
  if ( t.get()!=p.get() )
  {
    std::cout << "========1==========" << std::endl;
    std::cout << t.get() << std::endl;
    std::cout << p.get() << std::endl;
    return 1;
  }
  p.set(20);

  if ( t.get()!=p.get() )
  {
    std::cout << "========2==========" << std::endl;
    std::cout << t.get() << std::endl;
    std::cout << p.get() << std::endl;
    return 1;
  }
  
  int d[]={1,2,3,4};
  const test<aspect>::creator_type& c = t.vector(d, d + 4);
  if ( c.size()!=4 )
    return 1;
  
  return 0;
}
