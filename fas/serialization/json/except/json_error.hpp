#ifndef FAS_SERIALIZATION_JSON_EXCEPT_JSON_ERROR_HPP
#define FAS_SERIALIZATION_JSON_EXCEPT_JSON_ERROR_HPP

#include <string>
#include <stdexcept>

namespace fas{ namespace json{

class json_error
  : public std::runtime_error
{

public:
  typedef std::ptrdiff_t size_type;

  json_error(const std::string& msg, size_type tail_of = 0 )
    : std::runtime_error(msg)
    , _tail_of(tail_of)
  { }

  size_type tail_of() const { return _tail_of; }

  template<typename R>
  std::string message( R r ) const
  {
    if ( r.distance() < _tail_of )
      return this->what();

    std::string msg;
    msg = this->what();

    size_type dist = r.distance() - _tail_of;
    typename R::iterator beg_err = r.begin();
    std::advance(beg_err, dist);

    msg += std::string(": ") + std::string(r.begin(), beg_err ) + ">>>" + std::string(beg_err, r.end() );
    return msg;
  };

private:
  std::ptrdiff_t _tail_of;

};

}}

#endif
