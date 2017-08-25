#include <fas/testing/suite_counts.hpp>

::fas::testing::suite_counts fas_testing(int argc, char* argv[]);

int main(int argc, char* argv[])
{
  ::fas::testing::suite_counts sc = fas_testing(argc, argv);
  return sc.errors + sc.fails + sc.fatals + sc.crash;
}

