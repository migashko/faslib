#include "units789.hpp"

#include <fas/testing/suite.hpp>

BEGIN_SUITE(suite79, "suite79 description" )
  ADD_UNIT(unit7)
  ADD_UNIT(unit8)
  ADD_UNIT(unit9)
END_SUITE(suite79)

BEGIN_SUITE(suite79_skip, "Этот suit будет пропущен" )
  ADD_UNIT(unit7)
END_SUITE(suite79_skip)
