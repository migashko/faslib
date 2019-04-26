//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2019
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_SYSTEM_NULLPTR_HPP
#define FAS_SYSTEM_NULLPTR_HPP

#if __cplusplus > 199711L
  #if defined(__GNUC__) && (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 9))
    #define fas_nullptr nullptr
    #define fas_null_param nullptr
    #define fas_nullptr_t nullptr_t
  #else
    #define fas_nullptr    nullptr
    #define fas_null_param static_cast<void*>(nullptr)
  #endif
#else
  #define fas_null_param static_cast<void*>(0)
  const                         /* this is a const object...     */
  class fas_nullptr_t
  {
  public:
    template<class T>          /* convertible to any type       */
    operator T*() const        /* of null non-member            */
        { return NULL; }           /* pointer...                    */

    template<class C, class T> /* or any type of null           */
        operator T C::*() const /* member pointer...             */
        { return NULL; }   

  private:
    void operator&() const;    /* Can't take address of nullptr */

  } fas_nullptr = {};     
#endif

#endif
