#ifndef FAS_SERIALIZATION_JSON_PARSER_AD_STRING_HPP
#define FAS_SERIALIZATION_JSON_PARSER_AD_STRING_HPP

#include <fas/serialization/json/except/try_throw.hpp>
#include <fas/serialization/json/except/unexpected_end_fragment.hpp>
#include <fas/serialization/json/except/invalid_json_string.hpp>
#include <fas/serialization/json/except/expected_of.hpp>
#include <fas/serialization/json/except/out_of_range.hpp>
#include <fas/serialization/json/parser/tags.hpp>
#include <fas/range/distance.hpp>

namespace fas{ namespace json{ namespace parse{

struct ad_string
{

  template<typename T, typename R>
  bool check( T&, R r) { return r && *r=='"' ; }

  template<typename T, typename R>
  R operator()(T& t, R r)
  {
    return this->parse(t, r);
  }

  template<typename T, typename R, typename RD>
  std::pair<R, RD> operator()(T& t, R r, RD rd)
  {
    return this->copy(t, r, rd);
  }

private:
  
  template<typename T, typename R>
  R parse_hex(T& t, R r)
  {
    if (!r)
      return throw_( t, unexpected_end_fragment(), r);

    for (register int i=0; i < 4; ++i, ++r)
    {
      if (!r)
        return throw_( t, unexpected_end_fragment(), r);

      if ( ( *r < '0' || *r>'9')
             && (*r < 'A' || *r>'F')
             && (*r < 'a' || *r>'f') )
               return throw_( t, invalid_json_string( distance(r) ), r);
    }

    return r;
  }

  template<typename T, typename R, typename RD>
  R copy_hex(T& t, R r, RD& rd)
  {
    if (!r)
      return throw_( t, unexpected_end_fragment(), r);

    for (register int i=0; i < 4 ; ++i, ++r, ++rd)
    {
      if (!r)
        return throw_( t, unexpected_end_fragment(), r);
      
      if (!rd)
        return throw_( t, out_of_range(), r);

      if ( ( *r < '0' || *r > '9')
             && (*r < 'A' || *r > 'F')
             && (*r < 'a' || *r > 'f') )
               return throw_( t, invalid_json_string( distance(r) ), r);
               
      *rd = *r;
    }

    return r;
  }

  template<typename T, typename R>
  R parse_symbol(T& t, R r)
  {
    /*
    0x00000000 — 0x0000007F: 0xxxxxxx
    0x00000080 — 0x000007FF: 110xxxxx 10xxxxxx
    0x00000800 — 0x0000FFFF: 1110xxxx 10xxxxxx 10xxxxxx
    0x00010000 — 0x001FFFFF: 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
    */
    if (!r)
      return throw_( t, unexpected_end_fragment(), r);
      

    if ( (*r & 128)==0 )
      return ++r;
    if ( (*r & 224)==192 && ++r && (*r & 192)==128 )
      return ++r;
    if ( (*r & 240)==224 && ++r && (*r & 192)==128 && ++r && (*r & 192)==128 )
      return ++r;
    if ( (*r & 248)==240 && ++r && (*r & 192)==128 && ++r && (*r & 192)==128 && ++r && (*r & 192)==128)
      return ++r;

    if ( r )
      return throw_( t, invalid_json_string( distance(r) ), r);

    return throw_( t, unexpected_end_fragment(), r);
    
  }

  template<typename T, typename R, typename RD>
  R copy_symbol(T& t, R r, RD& rd)
  {
    /*
    0x00000000 — 0x0000007F: 0xxxxxxx
    0x00000080 — 0x000007FF: 110xxxxx 10xxxxxx
    0x00000800 — 0x0000FFFF: 1110xxxx 10xxxxxx 10xxxxxx
    0x00010000 — 0x001FFFFF: 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
    */
    if (!r)
      return throw_( t, unexpected_end_fragment(), r);

    if ( (*r & 128)==0 )
    {
      if (!rd)
        return throw_( t, out_of_range(), r);
      
      *(rd++) = *(r++);
      
      return r;
    }

    if ( (*r & 224)==192 )
    {
      if (!rd)
        return throw_( t, out_of_range(), r);
      
      *(rd++) = *(r++);
      
      if ( r && (*r & 192)==128 )
      {
        if (!rd)
          return throw_( t, out_of_range(), r);
        
        *(rd++) = *(r++);
        
        return r;
      }
    }
    
    if ( (*r & 224)==192 )
    {
      if (!rd)
        return throw_( t, out_of_range(), r);
      
      *(rd++) = *(r++);
      
      if ( r && (*r & 192)==128 )
      {
        *(rd++) = *(r++);
        
        if ( r && (*r & 192)==128 )
        {
          if (!rd)
            return throw_( t, out_of_range(), r);
          
          *(rd++) = *(r++);
          
          return r;
        }
      }
    }

    if ( (*r & 224)==192 )
    {
      if (!rd)
        return throw_( t, out_of_range(), r);
      
      *(rd++) = *(r++);
      
      if ( r &&  (*r & 192)==128 )
      {
        if (!rd)
          return throw_( t, out_of_range(), r);
        
        *(rd++) = *(r++);
        
        if ( r &&  (*r & 192)==128 )
        {
          if (!rd)
            return throw_( t, out_of_range(), r);
          
          *(rd++) = *(r++);
          
          if ( r && (*r & 192)==128 )
          {
            if (!rd)
              return throw_( t, out_of_range(), r);
            *(rd++) = *(r++);
            return r;
          }
        }
      }
    }

    if ( r )
      return throw_( t, invalid_json_string( distance(r) ), r);
    
    return throw_( t, unexpected_end_fragment(), r);
  }

  template<typename T, typename R>
  R parse(T& t, R r)
  {
    if (!r)
      return throw_( t, unexpected_end_fragment(), r);

    if (*r!='"') 
      return throw_( t, expected_of("\"",  distance(r) ), r);

    for ( ++r; r && *r!='"'; )
    {
      if (*r=='\\')
      {
        if ( !(++r) )
          return throw_( t, unexpected_end_fragment(), r);

        if ( *r != '"' && *r != '\\' && *r != '/'
             && *r != 't' && *r != 'b' && *r != 'n'
             && *r != 'r' && *r != 'f' && *r != 'u'
           )
            return throw_( t, invalid_json_string( distance(r) ), r);
             

        if ( *(r++) == 'u' )
        {
          r = this->parse_hex(t, r);
          if ( !try_(t) )
            return r;
        }
      }
      else
      {
        r = this->parse_symbol(t, r);
        if ( !try_(t) )
          return r;
      }
    }

    if (!r)
      return throw_( t, unexpected_end_fragment(), r);

    if (*r!='"')
      return throw_( t, expected_of("\"", distance(r) ), r);

    return ++r;
  }

  template<typename T, typename R, typename RD>
  std::pair<R, RD> copy(T& t, R r, RD& rd)
  {
    if (!r)
      return throw_( t, unexpected_end_fragment(), r, rd);

    if (*r!='"') 
      return throw_( t, expected_of("\"",  distance(r) ), r, rd);

    if (!rd)
      return throw_( t, out_of_range(), r, rd);
    
    *(rd++) = *(r++);
    
    for ( ; r && *r!='"'; )
    {
      if (*r=='\\')
      {
        if (!rd) 
          return throw_( t, out_of_range(), r, rd);

        *(rd++) = *(r++);
        
        if ( !r ) 
          return throw_( t, unexpected_end_fragment(), r, rd);

        if ( *r != '"' && *r != '\\' && *r != '/'
             && *r != 't' && *r != 'b' && *r != 'n'
             && *r != 'r' && *r != 'f' && *r != 'u'
           )
            return throw_( t, invalid_json_string( distance(r) ), r, rd);

        if (!rd) 
          return throw_( t, out_of_range(), r, rd);

        *(rd++) = *r;

        if ( *(r++) == 'u' )
        {
          r = this->copy_hex(t, r, rd);
          if ( !try_(t) )
            return std::make_pair(r, rd);
        }

      }
      else
      {
        r = this->copy_symbol(t, r, rd);
        if ( !try_(t) )
          return std::make_pair(r, rd);
      }
    }

    if (!r)
      return throw_( t, unexpected_end_fragment(), r, rd);

    if (*r!='"')
      return throw_( t, expected_of("\"", distance(r) ), r, rd);

    if (!rd) 
      return throw_( t, out_of_range(), r, rd);
    
    *(rd++) = *(r++);
    
    return std::make_pair(r, rd);
  }

};

}}}

#endif
