//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2012
//
// Copyright: See COPYING file that comes with this distribution
//

template<typename T, typename E>
inline void throw_( T& t, const E& e)
{
  return ::fas::serialization::throw_t<_except_>(t, e );
}

template<typename T, typename E, typename R>
inline R throw_( T& t, const E& e, R r)
{
  return ::fas::serialization::throw_t<_except_>(t, e, r);
}

template<typename T, typename E, typename R, typename RR>
inline std::pair<R, RR> throw_( T& t, const E& e, R r, RR rr) 
{
  return ::fas::serialization::throw_t<_except_>(t, e, r, rr);
}

template<typename T>
inline bool try_( T& t)
{
  return ::fas::serialization::try_t<_except_>(t);
}
