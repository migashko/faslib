#include <fas/testing.hpp>

#include <fas/aop/value_advice.hpp>
#include <fas/adv/ad_container_manager.hpp>
#include <fas/adv/ad_aspect_select.hpp>
#include <vector>

struct _vector_;

UNIT(ad_container_manager_test, "ad_container_manager")
{
  using namespace ::fas;
  using namespace ::fas::testing;
  
  ad_container_manager<_vector_> acm;
  acm.initialize(t);
  acm.clear(t);
  acm.dispose(t);
  
  typename ad_container_manager<_vector_>::orange_type_t<T>::type r = acm.orange(t);
  *(r++) = 1;
  *(r++) = 2;
  *(r++) = 3;
  
  typename ad_container_manager<_vector_>::range_type_t<T>::type rr = acm.range(t);
  
  t << equal<assert>( (int) rr.distance(), 3 ) << FAS_TESTING_FILE_LINE;
  t << equal<assert>( (int) *(rr++), 1 ) << FAS_TESTING_FILE_LINE;
  t << equal<assert>( (int) *(rr++), 2 ) << FAS_TESTING_FILE_LINE;
  t << equal<assert>( (int) *(rr++), 3 ) << FAS_TESTING_FILE_LINE;
}

struct _test_;

UNIT(ad_select_aspect_test1, "ad_select_aspect 1")
{
  using namespace ::fas;
  using namespace ::fas::testing;

  typedef aspect_class< aspect< value_advice<_test_, int> > > class1;
  
  
  typedef switch_by_tag_t<_test_> aspect_select;
  aspect_select aas;
  class1 c1;
  aas.advice(c1)=10;
  aas(c1).get_aspect().template get<_test_>()=10;
  enum { result = static_check< some_type< int, aspect_select::select_t<class1>::advice_type >::value >::value };
}

UNIT(ad_select_aspect_test2, "ad_select_aspect 2")
{
  using namespace ::fas;
  using namespace ::fas::testing;

  typedef aspect_class< aspect< value_advice<_test_, int> > > class1;
  typedef aspect_class< aspect< value_advice<_test_, std::string> > > class2;
  
  
  typedef switch_by_tag_t<_test_> aspect_select;
  aspect_select aas;
  class1 c1;
  class2 c2;
  aas.advice(c1, c2)=10;
  aas(c1, c2).get_aspect().template get<_test_>()=10;
  aas.advice(c2, c1)="string";
  aas(c2, c1).get_aspect().template get<_test_>()="string";
  
  enum { 
    result = static_check< some_type< int, aspect_select::select_t<class1, class2>::advice_type >::value >::value 
             + static_check< some_type< std::string, aspect_select::select_t<class2, class1>::advice_type >::value >::value 
    
  };
}

UNIT(ad_select_aspect_test2_1, "ad_select_aspect 2.1")
{
  using namespace ::fas;
  using namespace ::fas::testing;

  typedef aspect_class< aspect< value_advice<_test_, int> > > class1;
  typedef aspect_class< aspect< > > class2;
  
  
  typedef switch_by_tag_t<_test_> aspect_select;
  aspect_select aas;
  class1 c1;
  class2 c2;
  aas.advice(c1, c2)=10;
  aas.advice(c2, c1)=10;
  
  enum { 
    result = static_check< some_type< int, aspect_select::select_t<class1, class2>::advice_type >::value >::value 
             + static_check< some_type< int, aspect_select::select_t<class2, class1>::advice_type >::value >::value 
	     //+ static_check< class2::aspect::template has_advice<_test_>::helper::value >::value 
    
  };
}

UNIT(ad_select_aspect_test3, "ad_select_aspect 3")
{
  using namespace ::fas;
  using namespace ::fas::testing;

  typedef aspect_class< aspect< value_advice<_test_, int> > > class1;
  typedef aspect_class< aspect< value_advice<_test_, std::string> > > class2;
  typedef aspect_class< aspect< value_advice<_test_, float> > > class3;
  
  
  typedef switch_by_tag_t<_test_> aspect_select;
  aspect_select aas;
  class1 c1;
  class2 c2;
  class3 c3;
  aas.advice(c1, c2, c3)=10;
  aas.advice(c2, c1, c3)="string";
  aas.advice(c3, c1, c2) = static_cast<float>(3.14);
  
  /*std::cout << aas(c2, c1) << std::endl;
  std::cout << aas(c1, c2) << std::endl;*/
  enum { 
    result = static_check< some_type< int, aspect_select::select_t<class1, class2, class3>::advice_type >::value >::value 
             + static_check< some_type< std::string, aspect_select::select_t<class2, class1, class3>::advice_type >::value >::value
             + static_check< some_type< float, aspect_select::select_t<class3, class2, class1>::advice_type >::value >::value 
    
  };
}

UNIT(ad_select_aspect_test3_1, "ad_select_aspect 3.1")
{
  using namespace ::fas;
  using namespace ::fas::testing;

  typedef aspect_class< aspect< value_advice<_test_, int> > > class1;
  typedef aspect_class< aspect<  > > class2;
  typedef aspect_class< aspect<  > > class3;
  
  
  typedef switch_by_tag_t<_test_> aspect_select;
  aspect_select aas;
  class1 c1;
  class2 c2;
  class3 c3;
  aas.advice(c1, c2, c3)=10;
  aas.advice(c2, c1, c3)=10;
  aas.advice(c3, c1, c2)=10;
  
  /*std::cout << aas(c2, c1) << std::endl;
  std::cout << aas(c1, c2) << std::endl;*/
  enum { 
    result = static_check< some_type< int, aspect_select::select_t<class1, class2, class3>::advice_type >::value >::value 
             + static_check< some_type< int, aspect_select::select_t<class2, class1, class3>::advice_type >::value >::value
             + static_check< some_type< int, aspect_select::select_t<class3, class2, class1>::advice_type >::value >::value 
    
  };
}

BEGIN_SUITE(managers_suite, "buffer managers suite")
ADD_UNIT(ad_container_manager_test)
ADD_UNIT(ad_select_aspect_test1)
ADD_UNIT(ad_select_aspect_test2)
ADD_UNIT(ad_select_aspect_test2_1)
ADD_UNIT(ad_select_aspect_test3)
ADD_ADVICE( _vector_, std::vector<char> )
END_SUITE(managers_suite)

