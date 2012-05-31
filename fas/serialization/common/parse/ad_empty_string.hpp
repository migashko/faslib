#ifndef FAS_SERIALIZATION_COMMON_PARSER_AD_EMPTY_STRING_HPP
#define FAS_SERIALIZATION_COMMON_PARSER_AD_EMPTY_STRING_HPP

namespace fas{ namespace serialization{ namespace parse{
	
struct ad_empty_string
{
  template<typename T, typename R>
  bool check( T&, R ) 
  {
    return false;
  }
  
  template<typename T, typename R>
  R operator()(T&, R r)
  {
    return r;
  }
  
  template<typename T, typename R, typename RO>
  std::pair<R, RO> operator()(T& t, R r, RO ro)
  {
    return std::make_pair(r, ro);
  }
 
};

}}}

#endif
