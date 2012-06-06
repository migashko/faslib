#ifndef FAS_SERIALIZATION_JSON_SERIALIZER_SERIALIZE_STRING_HPP
#define FAS_SERIALIZATION_JSON_SERIALIZER_SERIALIZE_STRING_HPP

#include <fas/serialization/misc/integer_serializer.hpp>

namespace fas { namespace json{

template<typename SR, typename R>
inline R serialize_string(SR sr, R r)
{
  if (!r) return r;
  *(r++)='"';

  for ( ;sr && r && *sr!='\0'; ++sr )
  {
    switch ( *sr )
    {
      case '"' :
      case '\\':
      case '/' :  *(r++)='\\'; if (r) *(r++) = *sr; break;
      case '\t':  *(r++)='\\'; if (r) *(r++) = 't'; break;
      case '\b':  *(r++)='\\'; if (r) *(r++) = 'b'; break;
      case '\r':  *(r++)='\\'; if (r) *(r++) = 'r'; break;
      case '\n':  *(r++)='\\'; if (r) *(r++) = 'n'; break;
      case '\f':  *(r++)='\\'; if (r) *(r++) = 'f'; break;
      default: *(r++) = *sr; break;
    }
  }

  if ( r ) *(r++)='"';
  
  return r;
}

}}

#endif

