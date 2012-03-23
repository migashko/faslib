
#ifndef FAS_XTIME_XSPAN_HPP
#define FAS_XTIME_XSPAN_HPP

#include <fas/xtime/types.hpp>

namespace fas {

template<long F, long T>
inline long xsec_convert(long xsec)
{
  // F MICRO
  // T NANO
  // (xsec * FAS_NANOSEC/F) - nanosec
  return static_cast<long> ( static_cast<xsec_t>( xsec ) * T / F );
  /*
  return (xsec * (FAS_NANOSEC/F)) * T/FAS_NANOSEC;
  
          FAS_NANOSEC         T
  xsec *  ------------  * ---------------
               F            FAS_NANOSEC
               */
};
  
template<long I>
struct xspan
{
  static const xsec_t xmax = I;
  
  template<long F>
  static long convert(long xsec)
  {
    return static_cast<long> ( static_cast<xsec_t>( xsec ) * xmax / F );
  };

  long sec;

  long xsec;

  xspan(): sec(0), xsec(0) {}
  
  template<long X>
  xspan(const xspan<X>& span )
    : sec(span.sec)
    , xsec( convert<xspan<X>::xmax>(span.xsec))
  {}

/*
  xspan(const xspan<FAS_NANOSEC>& span )
    : sec(span.sec)
    , xsec(xsec_convert<FAS_NANOSEC,xmax>(span.xsec))
  {
  }

  xspan(const xspan<FAS_MICROSEC>& span )
    : sec(span.sec)
    , xsec(xsec_convert<FAS_MICROSEC,xmax>(span.xsec))
  {
  }

  xspan(const xspan<FAS_MILLISEC>& span )
    : sec(span.sec)
    , xsec(xsec_convert<FAS_MILLISEC, xmax>(span.xsec))
  {
  }
  */

  xspan(long sec, long xsec): sec(sec), xsec(xsec) {}

  xspan(long long sec): sec(static_cast<long>(sec) ), xsec(0) {}

  xspan(int sec): sec(sec), xsec(0) {}

  xspan(long sec): sec(sec), xsec(0) {}

  xspan(float s): sec( static_cast<long>(s) ), xsec( static_cast<long>( (s - sec)*xmax ) ) {}

  xspan(double s): sec( static_cast<long>(s) ), xsec( static_cast<long>( (s - sec)*xmax  ) ) {}

  xsec_t to_nanosec() const { return ( static_cast<xsec_t>(sec) * xmax + xsec) * (FAS_NANOSEC/xmax ); }
  xsec_t to_microsec() const { return to_nanosec()/1000; }
  xsec_t to_millisec() const { return to_nanosec()/1000000; }
  xsec_t to_centisec() const { return to_nanosec()/10000000; }
  xsec_t to_decisec() const { return to_nanosec()/100000000; }
  
  float to_float() const { return static_cast<float>( to_nanosec() ) / xmax; }
  double to_double() const { return static_cast<double>( to_nanosec() ) / xmax; }
  
  template<long X>
  xspan& operator += (const xspan<X>& s) { *this = *this + s;  return *this; }

  template<typename T>
  xspan& operator += (const T& s) { *this = *this + xspan<I>(s);  return *this; }

  template<long X>
  xspan& operator -= (const xspan<X>& s) { *this = *this - s;  return *this; }

  template<typename T>
  xspan& operator -= (const T& s) { *this = *this - xspan<I>(s);  return *this; }

  template<long X>
  xspan& operator /= (const xspan<X>& s) { *this = *this / s;  return *this; }

  template<typename T>
  xspan& operator /= (const T& s) { *this = *this / xspan<I>(s);  return *this; }

  template<long X>
  xspan& operator *= (const xspan<X>& s) { *this = *this * s;  return *this; }

  template<typename T>
  xspan& operator *= (const T& s) { *this = *this * xspan<I>(s);  return *this; }

};

/*
typedef xspan<FAS_NANOSEC> nanospan;
typedef xspan<FAS_MICROSEC> microspan;
typedef xspan<FAS_MILLISEC> millispan;
*/

/*
struct nanospan
{
  long sec;

  long xsec;

  nanospan(): sec(0), xsec(0) {}

  nanospan(long sec, long xsec): sec(sec), xsec(xsec) {}

  nanospan(long long sec): sec(sec), xsec(0) {}

  nanospan(int sec): sec(sec), xsec(0) {}

  nanospan(long sec): sec(sec), xsec(0) {}

  nanospan(float s): sec(s), xsec((s - sec)*FAS_NANOSEC) {}

  nanospan(double s): sec(s), xsec((s - sec)*FAS_NANOSEC) {}

  nanospan& operator -= (const nanospan& s)
  {
    bool flag = xsec < s.xsec;
    sec -= s.sec - flag;
    xsec -= s.xsec + flag * FAS_NANOSEC;
    return *this;
  }

  xsec_t to_nanosec() const { return static_cast<xsec_t>(sec) * FAS_NANOSEC + xsec; }
  xsec_t to_microsec() const { return to_nanosec()/1000; }
  xsec_t to_millisec() const { return to_nanosec()/1000000; }
  xsec_t to_centisec() const { return to_nanosec()/10000000; }
  xsec_t to_decisec() const { return to_nanosec()/100000000; }

  float to_float() const { return static_cast<float>( to_nanosec() ) / FAS_NANOSEC; }
  double to_double() const { return static_cast<double>( to_nanosec() ) / FAS_NANOSEC; }
};
*/
/*
inline nanospan operator - (const nanospan& f,  const nanospan& s)
{
  bool flag = f.xsec < s.xsec;
  return nanospan(
    f.sec - s.sec - flag,
    f.xsec - s.xsec + flag * FAS_NANOSEC
  );
}

inline nanospan operator + (const nanospan& f,  const nanospan& s)
{
  bool flag = (f.xsec + s.xsec >= FAS_NANOSEC);
  return nanospan(
    f.sec + s.sec + flag,
    f.xsec + s.xsec - flag * FAS_NANOSEC
  );
}


inline nanospan operator / (const nanospan& s, const nanospan& f)
{
  if ( f.xsec == 0)
  {
    xsec_t xsec = s.to_nanosec()/f.sec;
    return nanospan(
          xsec / FAS_NANOSEC,
          xsec % FAS_NANOSEC
    );
  }
  else
    return nanospan( s.to_double() / f.to_double() );
  
};

inline nanospan operator * (const nanospan& s, const nanospan& f)
{
  if ( f.xsec == 0)
  {
    xsec_t xsec = s.to_nanosec()*f.sec;
    return nanospan(
          xsec / FAS_NANOSEC,
          xsec % FAS_NANOSEC
    );
  }
  else
    return nanospan( s.to_double() * f.to_double() );
 
};

inline bool operator == (const nanospan& f,  const nanospan& s)
{
  return f.sec == s.sec && f.xsec == s.xsec;
}

inline bool operator != (const nanospan& f,  const nanospan& s)
{
  return !(f == s);
}

inline bool operator < (const nanospan& f,  const nanospan& s)
{
  if ( f.sec < s.sec ) return true;
  return f.xsec < s.xsec;
}

inline bool operator > (const nanospan& f,  const nanospan& s)
{
  if ( f.sec > s.sec ) return true;
  return f.xsec > s.xsec;
}

inline bool operator <= (const nanospan& f,  const nanospan& s)
{
  return !( f > s );
}

inline bool operator >= (const nanospan& f,  const nanospan& s)
{
  return !( f < s );
}
*/


}

#endif
