#ifndef FAS_SERIALIZATION_JSON_SERIALIZER_SERIALIZE_NULL_HPP
#define FAS_SERIALIZATION_JSON_SERIALIZER_SERIALIZE_NULL_HPP

namespace fas { namespace json{

template<typename R>
inline R serialize_null(R r)
{
  if (r) *(r++) = 'n';
  if (r) *(r++) = 'u';
  if (r) *(r++) = 'l';
  if (r) *(r++) = 'l';
  return r;
}

}}

#endif

