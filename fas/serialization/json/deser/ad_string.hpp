#ifndef FAS_SERIALIZATION_JSON_DESER_AD_STRING_HPP
#define FAS_SERIALIZATION_JSON_DESER_AD_STRING_HPP

#include <fas/serialization/json/except/try_throw.hpp>
#include <fas/serialization/json/except/out_of_range.hpp>
#include <fas/serialization/json/except/unexpected_end_fragment.hpp>
#include <fas/serialization/json/except/invalid_json_string.hpp>
#include <fas/serialization/json/except/expected_of.hpp>

#include <fas/serialization/json/deser/tags.hpp>
#include <fas/serialization/json/parser/tags.hpp>

// #include <fas/range/range.hpp>

//#include <fas/typemanip/type2type.hpp>

#include <fas/typemanip/is_array.hpp>
#include <fas/range/range.hpp>
#include <fas/range/orange.hpp>
#include <fas/range/distance.hpp>





#include <fas/serialization/common/deser/ad_string.hpp>
/*
using ::fas::serialization::throw_t;
using ::fas::serialization::try_t;
*/

namespace fas{ namespace json{ namespace deser{

struct ad_uhex:
	::fas::serialization::deser::ad_json_uhex<_except_>
{
	
};

struct ad_utf8:
	::fas::serialization::deser::ad_utf8<_except_>
{

};

struct ad_escape:
	::fas::serialization::deser::ad_json_escape<_uhex_, _except_>
{
	
};
	
struct ad_content_string:
	::fas::serialization::deser::ad_jsonbase_string_t<_quotes_, _utf8_, _escape_, _except_>
{
};

	
struct ad_string:
	::fas::serialization::deser::ad_json_string_t<_content_string_, _quotes_, parse::_string_, parse::_null_, _except_>
{
};

struct string_aspect:	aspect< type_list_n<
	advice< _uhex_, ad_uhex>,
	advice< _utf8_, ad_utf8>,
	advice< _escape_, ad_escape>,
	advice< _content_string_, ad_content_string>,
	advice< _string_, ad_string>
>::type> {};

struct ad_cstring
{
private:
  template<typename R, typename RS>
  bool _check(R& r, RS rs)
  {
    for ( ;r && rs && *r==*rs; ++r, ++rs );
    return !rs && r && *r=='"';
  }
public:

  template<typename T, typename M, typename R>
  bool check(T& t, M, R r)
  {
    return t.get_aspect().template get<parse::_string_>().check(r);
  };

  template<typename T, typename M, typename V, typename R>
  R operator()(T& t, M, V&, R r)
  {
    if ( !t.get_aspect().template get<parse::_string_>().check(r) )
      return r;

    R income =  r;
    if (!_check(++r, M().get_range() ) )
    {
      if (!r)
        throw unexpected_end_fragment();
      return income;
    }
    if (!r)
      throw unexpected_end_fragment();

    if ( *r++ != '"')
      return income;
    
    return r;
  }
};

}}}

#endif
