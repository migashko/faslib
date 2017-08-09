//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#include <fas/typemanip.hpp>
#include <fas/static_check.hpp>

#include <vector>
#include <set>
#include <iterator>

using namespace ::fas;

struct A{ };

struct B:A
{
  typedef int test_type;
  
  template<typename T>
  struct apply
  {
    enum { value = T::value };
  };
};

struct C:A{};
struct D:B,C{};

struct VB: virtual A{};
struct VC: virtual A{};
struct VD: virtual VB, virtual VC{};

// cppcheck-suppress functionStatic
struct M0 { void member0() {}; };
// cppcheck-suppress functionStatic
struct M1: M0 { void member1(int) {}; };
// cppcheck-suppress functionStatic
struct M2: M1 { void member2(int, int) {}; };
// cppcheck-suppress functionStatic
struct M3: M2 { void member3(int, int, int) {}; };
// cppcheck-suppress functionStatic
struct M4: M3 { void member4(int, int, int, int) {}; };
// cppcheck-suppress functionStatic
struct M5: M4 { void member5(int, int, int, int, int) {}; };

FAS_HAS_TYPENAME(has_test_type, test_type)
FAS_HAS_TEMPLATE1(has_apply, apply)
FAS_HAS_MEMBER_FUNCTION0(has_member0, member0, void)
FAS_HAS_MEMBER_FUNCTION1(has_member1, member1, void, int)
FAS_HAS_MEMBER_FUNCTION2(has_member2, member2, void, int, int)
FAS_HAS_MEMBER_FUNCTION3(has_member3, member3, void, int, int, int)
FAS_HAS_MEMBER_FUNCTION4(has_member4, member4, void, int, int, int, int)
FAS_HAS_MEMBER_FUNCTION5(has_member5, member5, void, int, int, int, int, int)

template < typename T, typename U, void (T::*)(const U&) > struct op_mf3 {};
int main()
{
  enum {
    test1 = static_check< !has_test_type<A>::value >::value,
    test2 = static_check< has_test_type<B>::value >::value,
    test1_some_type = static_check< same_type< bool, bool >::value >::value,
    test2_some_type = static_check< !same_type< int*, float*>::value >::value,
    test3_some_type = static_check< !same_type< int, const int>::value >::value,
    test1_conv_type = static_check< conversion< int, long >::value >::value,
    test2_conv_type = static_check< !conversion< int*, char*>::value >::value,
    test3_conv_type = static_check< conversion< int*, const int* >::value >::value,
    test4_conv_type = static_check< !conversion< const int*, int* >::value >::value,
    test5_conv_type = static_check< conversion< int*, volatile int* >::value >::value,
    test6_conv_type = static_check< !conversion< volatile int*, int* >::value >::value,

    test1_abc_type = static_check< same_type< A, A >::value >::value,
    test2_abc_type = static_check< same_type< D, D >::value >::value,
    test3_abc_type = static_check< conversion< B, A >::value >::value,
    test4_abc_type = static_check< !conversion< A, B >::value >::value,
    test5_abc_type = static_check< conversion< B*, A* >::value >::value,
    test6_abc_type = static_check< !conversion< A*, B* >::value >::value,
    test7_abc_type = static_check< conversion< C, A >::value >::value,
    // 'A' is an ambiguous base of 'D'. use virtual inheritance
    // testt8_abc_type = static_check< conversion< D, A >::value >::value,
    test9_abc_type = static_check< conversion< D, B >::value >::value,
    testA_abc_type = static_check< conversion< D, C >::value >::value,
    // OK - virtual inheritance
    testB_abc_type = static_check< conversion< VD, A >::value >::value,
    testC = static_check< super_subclass< A, B >::value >::value,
    testD = static_check< super_subclass< A, A >::value >::value,
    testE = static_check< !super_subclass_strict< A, A >::value >::value,
    
    test_template = static_check< !has_apply<A>::value >::value
                    + static_check< has_apply<B>::value >::value,
                    
    test_method = 
            static_check< has_member0< M0 >::value >::value
          + static_check< has_member1< M1 >::value >::value
          + static_check< has_member2< M2 >::value >::value
          + static_check< has_member3< M3 >::value >::value
          + static_check< has_member4< M4 >::value >::value
          + static_check< has_member5< M5 >::value >::value
 					
  };
  return 0;
}

