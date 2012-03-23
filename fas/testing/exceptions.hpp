#ifndef FAS_TESTING_EXCEPTIONS_HPP
#define FAS_TESTING_EXCEPTIONS_HPP

#include <stdexcept>
#include <string>

#define FAS_TESTING_FILE_LINE __FILE__ << ": " << __LINE__

namespace fas{ namespace testing{

class exception
  : public std::logic_error
{
public:
  exception(const std::string& what="")
    : std::logic_error(what)
  {}
};

/** Не перывает suite*/
/*class statment_error
  : public exception
{
public:
  statment_error(const std::string& what="")
    : exception(what)
  {}
};
*/

/** Перывает unit, но не перывает suite*/
class fail_error
  : public exception
{
public:
  fail_error(const std::string& what="")
    : exception(what)
  {}
};

/**-- Перывает тестирование */
/** Перывает suite и переходит на следующий */
class fatal_error
  : public exception
{
public:
  fatal_error(const std::string& what="")
    : exception(what)
  {}
};


}}

#endif
