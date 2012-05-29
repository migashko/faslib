#include <fas/type_list/type_list_n.hpp>
#include <fas/aop/aspect.hpp>
#include <fas/typemanip/remove_cvrp.hpp>
#include <string>
#include <iostream>

using namespace fas;

namespace test{
class access
{
public:
	access()
		: _a(-1)
		, _b("-")
	{}

	void set_a(int value) { _a = value;}
	int  get_a() { return _a;}
	int  get_a() const { return _a;}

	void set_b(const std::string& value) { _b = value;}
	void set_b(const char* value) { _b = value;}
	const std::string&  get_b() { return _b;}
	const std::string&  get_b() const { return _b;}

private:
	int _a;
	std::string _b;
};

template<typename V, typename VT, VT (V::* mg)(void) const>
struct mem_fun_get
{
	VT operator()(const V& v)
  {
    return (v.*mg)();
  }
};

template<typename V, typename VT, void (V::* mg)(VT), typename VVT = typename remove_cvrp<VT>::type >
struct mem_fun_set
{
private:
	typedef VVT value_type;
public:
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

template<typename FG, typename FS, typename M>
struct getset { };

template<typename FG, typename M>
struct getter { };

template<typename FG, typename M>
struct setter { };

}

int main()
{
	
	typedef test::mem_fun_get< test::access, const std::string&, &test::access::get_b> getter_b;
	typedef test::mem_fun_set< test::access, const std::string&, &test::access::set_b> setter_b;
	
	typedef test::mem_fun_set< test::access, const char*, &test::access::set_b> setter_b2;
	test::access ac;
	std::cout << getter_b()(ac) << std::endl;
	setter_b()(ac) = "Hello world" ;
	std::cout << getter_b()(ac) << std::endl;
  return 0;
}
