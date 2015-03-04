#include <fas/testing/unit.hpp>
#include <fas/testing/statements.hpp>
#include <fas/testing/formatting.hpp>
#include <fas/system/colorized.hpp>

UNIT(unit1, "testing unit1")
{
  using namespace fas::console;
  using namespace fas::testing;
  t << is_false<expect>(true) << "is_false<expect>(true)";
  t << message("This is message.") << "This is "<< magenta << "color" << restore_colors <<" message description.";
}

UNIT(unit2, "testing unit2")
{
  using namespace fas::testing;
  t << warning("This is warning.") << "This is warning description.";
}

UNIT(unit3, "testing unit3")
{
  using namespace fas::testing;
  t << nothing;
}
