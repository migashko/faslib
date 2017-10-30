#include <fas/testing/unit.hpp>
#include <fas/testing/statements.hpp>
#include <fas/testing/formatting.hpp>

UNIT(unit7, "testing unit7")
{
  using namespace fas::testing;
  t << is_true<crash>(false) << "остановка теста ";
  t << stop;
}

UNIT(unit8, "Этот юнит будет пропущен")
{
  using namespace fas::testing;
  t << nothing;
}

UNIT(unit9, "Этот юнит будет пропущен")
{
  using namespace fas::testing;
  t << nothing;
}
