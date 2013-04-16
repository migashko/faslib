//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013
//
// Copyright: See COPYING file that comes with this distribution
//

#include <fas/aop.hpp>
#include <fas/type_list.hpp>
#include <fas/mp.hpp>

#include <iostream>

struct _value_;
struct _provider1_;
struct _provider2_;

template<typename T>
class provider
{
  typedef typename T::aspect::template advice_cast<_value_>::type::value_type value_type;
public:
  provider(T* t)
  {
    _target = t;
  }

  void set(const value_type& value)
  {
    _target->get_aspect().template get<_value_>()(*this, value);
  }

  const value_type& get() const
  {
    return _target->get_aspect().template get<_value_>()(*this);
  }


private:
  T* _target;
};

struct aspect: fas::aspect< fas::type_list_n<
  fas::advice< _provider1_, fas::provider< fas::w< provider< fas::_1 > > > >,
  fas::advice< _provider2_, fas::provider_t< provider> >,
  fas::advice< _value_, fas::value<int> >

>::type >{};

template<typename A>
class test
  : public fas::aspect_class<A>
{
  typedef test<A> self;
  typedef fas::aspect_class<A> super;
public:
  typedef typename super::aspect::template advice_cast<_value_>::type::value_type value_type;
  typedef typename super::aspect::template advice_cast<_provider1_>::type::template apply< self >::type provider1_type;
  typedef typename super::aspect::template advice_cast<_provider2_>::type::template apply< self >::type provider2_type;

  void set(const value_type& value)
  {
    super::get_aspect().template get<_value_>()(*this, value);
  }

  const value_type& get() const
  {
    return super::get_aspect().template get<_value_>()(*this);
  }

  provider1_type get_provider1()
  {
    return provider1_type(this);
  }

  provider2_type get_provider2()
  {
    return provider2_type(this);
  }
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
  return 0;
}
