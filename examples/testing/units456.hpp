#include <fas/testing/unit.hpp>


UNIT(unit4, "testing unit4")
{
  using namespace fas::testing;
  t << equal<expect, std::string>("first string", "second string") << FAS_FL;
}

UNIT(unit5, "testing unit5")
{
  using namespace fas::testing;
  t << equal<expect, bool>(10, false) << FAS_FL;
  t << equal<expect, int>(10, false) << FAS_FL;
}

UNIT(unit6, "testing unit6")
{
  using namespace fas::testing;
  t << is_false<assert>(true) << FAS_FL;
  t << stop; // break if assert
  t << message("это сообщение вы увидите.");
  t << message("You will not see this message.");
 
}
