#ifndef FAS_SERIALIZATION_JSON_DESER_AD_ENUMERATION_HPP
#define FAS_SERIALIZATION_JSON_DESER_AD_ENUMERATION_HPP

#include <fas/serialization/json/except.hpp>
#include <fas/serialization/json/deser/deserialize_integer.hpp>
#include <fas/serialization/json/deser/ad_array.hpp>
#include <fas/serialization/json/deser/tags.hpp>
#include <fas/serialization/json/parser/tags.hpp>

//#include <fas/serialization/json/deser/ad_field_list.hpp>

namespace fas{ namespace json{ namespace deser{

struct ad_enum_value
{
  template<typename T, typename M, typename R>
  bool check(T& t, M m, R r)
  {
     return t.get_aspect().template get<parser::_string_>().is_string(r)
            || t.get_aspect().template get<parser::_number_>().is_number(r)
            || t.get_aspect().template get<parser::_null_>().check(r);
  }

  template<typename T, typename M, typename V, typename R>
  R operator()(T& t, M m, V& v, R r)
  {
    typedef typename M::target target;
    typedef typename target::deserializer_tag deserializer_tag;
    R income = r;
    //if ( this->_check(++r, m.get_range() ) )
    if ( t.get_aspect().template get<deserializer_tag>().check(t, target(), r) )
    {
      v = static_cast<V>( M::value );
      return t.get_aspect().template get<deserializer_tag>()(t, target(), v, r);
      /*
      v = static_cast<V>( M::value );
      return ++r;
      */
    }
    return income;
  }
  
private:
  template<typename R, typename RS>
  bool _check(R& r, RS rs)
  {
    for ( ;r && rs && *r==*rs; ++r, ++rs );
    return !rs && r && *r=='"';
  }
};

struct ad_enumset_value
{
  template<typename T, typename M, typename R>
  bool check(T& t, M m, R r)
  {
     return t.get_aspect().template get<parser::_string_>().is_string(r)
            || t.get_aspect().template get<parser::_number_>().is_number(r);
  }

  template<typename T, typename M, typename V, typename R>
  R operator()(T& t, M m, V& v, R r)
  {
    typedef typename M::target target;
    typedef typename target::deserializer_tag deserializer_tag;
    
    if ( t.get_aspect().template get<deserializer_tag>().check(t, target(), r)  )
    {
      R income = r;
      r = t.get_aspect().template get<deserializer_tag>()(t, target(), v, r);
      if ( r!=income )
        v = v | static_cast<V>( M::value );
      else
        return income; 
    }
    return r;
    /*R income = r;
    if ( this->_check(++r, m.get_range() ) )
    {
      v |= static_cast<V>( M::value );
      std::cout << "v==" << v << " M::value==" << M::value << std::endl;
      return ++r;
    }
    return income;*/
  }
  
private:
  /*
  template<typename R, typename RS>
  bool _check(R& r, RS rs)
  {
    std::cout << "ad_enumset_value::_check: " << std::string(r.begin(), r.end() ) << "==" << std::string(rs.begin(), rs.end() ) << std::endl;
    for ( ;r && rs && *r==*rs; ++r, ++rs );
    return !rs && r && *r=='"';
  }
  */
};

//struct ad_enumeration: ad_primary_list_t<'|'>{};
struct ad_enumset: ad_array{};

struct ad_enumeration
{
  template<typename T, typename M, typename R>
  bool check(T& t, M, R r)
  {
    return t.get_aspect().template get<parser::_string_>().check(r)
           || t.get_aspect().template get<parser::_number_>().check(r);
  };

  template<typename T, typename M, typename V, typename R>
  R operator()(T& t, M, V& v, R r)
  {
    using namespace ::fas::json;
    if ( t.get_aspect().template get<parser::_null_>().check(r) )
    {
      r = t.get_aspect().template get<parser::_null_>()(t, r);
      v = V();
    }
    else if ( t.get_aspect().template get<parser::_number_>().check(r) )
    {
      int value;
      r = deserialize_integer( value, r);
      v = static_cast<V>(value);
    }
    else if ( t.get_aspect().template get<parser::_string_>().check(r) )
    {
      typedef typename M::target_list target_list;
      r = _(t, target_list(), v, r);
    }
    return r;
  }

private:

  /*
  template<typename R, typename RS>
  bool _check(R& r, RS rs)
  {
    for ( ;r && rs && *r==*rs; ++r, ++rs );
    return !rs && r && *r=='"';
  }*/

  template<typename T, typename EL, typename V, typename R>
  R _(T& t, EL, V& v, R r)
  {
    return _(t, type_list<typename EL::left_type, typename EL::right_type>(), v, r);
  }

  template<typename T, typename EL, typename ER, typename V, typename R>
  R _(T& t, type_list<EL, ER>, V& v, R r)
  {
    typedef typename EL::deserializer_tag deserializer_tag;
    R income = r;
    r = t.get_aspect().template get<deserializer_tag>()(t, EL(), v, r);
    if ( r != income )
      return r;
    /*
    if ( t.get_aspect().template get<deserializer_tag>().check(t, EL(), r) )
      return t.get_aspect().template get<deserializer_tag>()(t, EL(), v, r);
    */

    /*
    if ( _check(++r, EL().get_range() ) && r)
    {
      if ( *r++ == '"')
      {
        v = static_cast<V>( EL::value );
        return r;
      }
    }
    */
    
    if (!r)
      throw unexpected_end_fragment();
    
    return _(t, ER(), v, income);
  }

  template<typename T, typename V, typename R>
  R _(T& t, empty_list, V& v, R r)
  {
    v = V();
    return t.get_aspect().template get<parser::_string_>()(t, r);
  }


};

}}}

#endif
