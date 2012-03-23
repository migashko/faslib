#ifndef FAS_SERIALIZATION_JSON_DESER_DESERIALIZE_SEQUENCE_HPP
#define FAS_SERIALIZATION_JSON_DESER_DESERIALIZE_SEQUENCE_HPP

#include <fas/serialization/json/deser/default_space_parser.hpp>

namespace fas { namespace json{

// #warning меняем концепцию. без проверок - десериализуем, пока десериализуется

/** предполагаем что входной массив без пробелов или его парсит f
 *  f - возвращает указатель на ,
  */
template<typename AR, typename R, typename F>
inline R deserialize_sequence( AR ar, R r, F f )
{
  typedef typename AR::value_type value_type;
  if ( !ar || !r ) return r;
  
  R income = r;
  value_type v = value_type();
  R current = f( v, r );
  if ( current == r )
    return income;
  *(ar++) = v;
  r = current;
  for ( ; ar && r && *r==','; )
  {
    ++r;
    if ( !r )
      return income;
    v = value_type();
    current = f( v, r );
    if ( r == current )
      return income;
    *(ar++) = v;
    r = current;
  }
  return r;
}

/*
template<typename AR, typename R, typename F, typename FS>
inline R deserialize_sequence_old( AR ar, R r, F f, FS space_parser )
{
  typedef typename AR::value_type value_type;
  if ( ar && r)
  {
    if ( f.check(r) )
    {
      value_type v = value_type();
      r = f( v, r);
      *(ar++) = v;
    }
    else
      r = f(r);
    
    r = space_parser(r);
    for ( ; ar && r && *r==','; )
    {
      ++r;
      if ( !r ) throw unexpected_end_fragment();
      r = space_parser(r);

      if ( f.check(r) )
      {
        value_type v = value_type();
        r = f( v, r);
        *(ar++) = v;
      }
      else
        r = f(r);

      r = space_parser(r);
    }
  }
  return r;
};

template<typename AR, typename R, typename F>
inline R deserialize_sequence_old( AR ar, R r, F f)
{
  return deserialize_sequence_old(ar, r, f, deser::default_space_parser());
};
*/

}}

#endif

