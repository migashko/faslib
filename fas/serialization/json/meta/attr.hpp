//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_SERIALIZATION_JSON_META_ATTR_HPP
#define FAS_SERIALIZATION_JSON_META_ATTR_HPP

#include <fas/serialization/json/ser/tags.hpp>
#include <fas/serialization/json/deser/tags.hpp>

#include <fas/typemanip/remove_cvrp.hpp>
#include <fas/typemanip/const_if_const.hpp>

namespace fas{ namespace json{

template<typename V, typename VT, VT V::* m>
struct member
{
  template<typename VV>
  typename const_if_const<VT, VV>::type& operator()(VV& v) const
  {
    return v.*m;
  }
};

template<typename V, typename VT, VT V::* m>
struct member_get
{
	typedef const VT& value_type;
  value_type operator()(const V& v) const
  {
    return v.*m;
  }
};

template<typename V, typename VT, VT V::* m>
struct member_set
{
	typedef VT& value_type;
  value_type operator()(V& v) const
  {
    return v.*m;
  }
};

template<typename V, typename VT, VT (V::* mg)(void) const>
struct mem_fun_get
{
	typedef VT value_type;
	value_type operator()(const V& v)
  {
    return (v.*mg)();
  }
};

template<typename V, typename VT, void (V::* mg)(VT), typename VVT = typename remove_cvrp<VT>::type >
struct mem_fun_set
{
	typedef VVT value_type;

	value_type& operator()(V& v)
  {
		_obj = &v;
    return _value;
  }

  ~mem_fun_set()
	{
		(_obj->*mg)(_value);
	}
private:
	V* 				 _obj;
	value_type _value;
};

template<typename G, typename M>
struct getter: G
{
  typedef typename M::metatype metatype;
  typedef M target;

  typedef ser::_attr_ serializer_tag;
  typedef deser::_stub_ deserializer_tag;
};

template<typename S, typename M>
struct setter: S
{
  typedef typename M::metatype metatype;
  typedef M target;

  typedef ser::_stub_ serializer_tag;
  typedef deser::_attr_ deserializer_tag;
};

// accessor< member_get<>, member_set<>, integer >

template<typename G, typename S, typename M = empty_type>
struct accessor
{
  typedef typename M::metatype metatype;
  typedef M target;
	typedef ser::_attr_ serializer_tag;
	typedef deser::_attr_ deserializer_tag;

	template<typename V>
	typename if_c<
		is_const<V>::value,
		typename G::value_type,
		typename S::value_type
	>::type
	operator() (V& v)
	{
		typedef typename if_c<is_const<V>::value, G, S>::type acc;
		return acc()(v);
	}
};

template<typename GS, typename M >
struct accessor<GS, M, empty_type>: GS
{
  typedef typename M::metatype metatype;
  typedef M target;
	typedef ser::_attr_ serializer_tag;
	typedef deser::_attr_ deserializer_tag;
};



template<typename V, typename VT, VT V::* m, typename J>
struct attr
  : member<V, VT, m>
{
  typedef typename J::metatype metatype;
  typedef J target;
  typedef ser::_attr_ serializer_tag;
  typedef deser::_attr_ deserializer_tag;

	/*
  typedef typename remove_cvrp<VT>::type value_type;

  template<typename VV>
  typename const_if_const<VT, VV>::type& operator()(VV& v) const
  {
    return v.*m;
  }*/
  /*
  VT& operator()(V& v) const
  {
    return v.*m;
  }*/

  /*const VT& operator()(const V& v) const
  {
    return v.*m;
  }*/
};

}}

#endif
