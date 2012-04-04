#ifndef FAS_SERIALIZATION_JSON_DESER_AD_SEQUENCE_HPP
#define FAS_SERIALIZATION_JSON_DESER_AD_SEQUENCE_HPP

#include <fas/serialization/json/deser/default_space_parser.hpp>
#include <fas/serialization/json/deser/deserialize_sequence.hpp>
#include <fas/serialization/json/deser/f_item_deserialize.hpp>
#include <fas/range/range.hpp>

#include <fas/integral/bool_.hpp>
#include <fas/typemanip/type2type.hpp>
#include <fas/typemanip/is_array.hpp>

#include <fas/static_check/verifying.hpp>

namespace fas{ namespace json{ namespace deser{

struct sequence_error
{
  enum { value = 0 };
  struct sequence_limit_required;
  typedef sequence_limit_required error;
};

/// Если элемент не сериализован то пропускает его и берет следующий
template<char C>
struct ad_sequence_t
{
  template<typename T, typename M, typename R>
  bool check(T&, M, R)
  {
    return true;
  };

  template<typename T, typename M, typename V, typename R>
  R operator()(T& t, M, V& v, R r)
  {
    return _1(t, M(), v, r, typename is_array<V>::type(), int_<M::limit>() );
  }
  
private:

  template<typename T, typename M, typename V, typename R, typename ISA>
  R _1(T&, M, V& , R r, ISA, int_<0> ) { return r; }
  
  template<typename T, typename M, typename V, typename R, typename ISA>
  R _1(T& t, M, V& v, R r, ISA, int_<-1> )
  {
    if (!r) return r;

    typedef typename typerange<V>::orange range_type;
    range_type vr = orange(v);

    r = _2( t, M(), vr, r );

    _finalize(vr, typename is_array< V >::type() );

    return r;
  }

  template<typename T, typename M, typename V, typename R>
  R _1(T& t, M, V* v, R r, false_, int_<-1> )
  {
    typedef verifying< false_, sequence_error >::type sequence_limit_required;
    sequence_limit_required();
    // enum { sequence_limit_required = static_check< 0 >::value };
    return r;
  }

  template<typename T, typename M, typename V, typename R>
  R _1(T& t, M, V* v, R r, false_, int_<0> ) { return r; }


  template<typename T, typename M, typename V, typename R, int N>
  R _1(T& t, M, V* v, R r, false_, int_<N> )
  {
    if (!r || !v) return r;

    typedef typename typerange<V*>::range range_type;
    range_type vr = range(v, v + N);
    r = _2( t, M(), vr, r );
    _finalize(vr, true_() );
    return r;
  }

  template<typename T, typename M, typename VR, typename R>
  R _2(T& t, M, VR& vr, R r)
  {
    if ( !vr )
      return r;

    typedef typename M::target target;
    int counter = M::limit;
    r = _3<target>(t, vr, r, counter);
    for ( ; vr && r && *r==C && counter ; r = _3<target>(t, vr, ++r, counter) );
    return r;
  }
  
  
  template<typename Tg, typename T, typename VR, typename R>
  R _3(T& t, VR& varr, R r, int& counter )
  {
    typedef typename VR::value_type value_type;
    return _4<Tg>( t, varr, r, counter, typename is_array<value_type>::type() );
  }

  template<typename Tg, typename T, typename VR, typename R>
  R _4(T& t, VR& varr, R r, int& counter, false_ )
  {
    typedef Tg target;
    typedef typename target::deserializer_tag deserializer_tag;
    typedef typename VR::value_type value_type;
    
    value_type item = value_type();
    
    r = t.get_aspect().template get< parse::_space_ >()(t, r);
    R current = t.get_aspect().template get< deserializer_tag >()(t, target(), item, r);
    if ( r ==  current )
      r = t.get_aspect().template get< parse::_value_ >()(t, r);
    else
    {
      r = current;
      *(varr++) = item;
      --counter;
    }
    r = t.get_aspect().template get< parse::_space_ >()(t, r);
    return r;
  }

  template<typename Tg, typename T, typename VR, typename R>
  R _4(T& t, VR& varr, R r, int& counter, true_)
  {
    typedef Tg target;
    typedef typename target::deserializer_tag deserializer_tag;
    typedef typename VR::value_type value_type;
    
    r = t.get_aspect().template get< parse::_space_ >()(t, r);
    R current = t.get_aspect().template get< deserializer_tag >()(t, target(), *varr, r);
    if ( r ==  current )
      r = t.get_aspect().template get< parse::_value_ >()(t, r);
    else
    {
      r = current;
      ++varr;
      --counter;
    }
    r = t.get_aspect().template get< parse::_space_ >()(t, r);
    return r;
  }

  template<typename R>
  void _finalize( R, false_ ) {}

  template<typename R>
  void _finalize( R r, true_ )
  {
    typedef typename R::value_type value_type;
    typedef typename is_array< value_type >::type is_array_type;
    while ( r )
      _finalize2( *(r++), type2type<value_type>(), is_array_type() );
  }

  template<typename V>
  void _finalize2( V& v, type2type<V>, false_ )
  {
    v = V();
  }

  template<typename V, int N>
  void _finalize2( V* v, type2type<V[N]>, true_ )
  {
    for (register int i=0; i < N; ++i)
      _finalize2( v[i], type2type<V>(), typename is_array< V >::type() );
  }
};

struct ad_sequence: ad_sequence_t<','>{};


}}}


#endif
