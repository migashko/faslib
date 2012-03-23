#ifndef FAS_SERIALIZATION_JSON_SERIALIZE_SEQUENCE_HPP
#define FAS_SERIALIZATION_JSON_SERIALIZE_SEQUENCE_HPP

namespace fas { namespace json{

template<typename AR, typename R, typename F>
inline R serialize_sequence( AR ar, R r, F f )
{
  if ( ar && r)
  {
    r = f(*(ar++), r);
    for ( ; ar && r;)
    {
      *r++ = ',';
      if (r)
        r = f(*(ar++), r);
    }
  }
  return r;
};


}}

#endif

