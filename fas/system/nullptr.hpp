//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2019
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_SYSTEM_NULLPTR_HPP
#define FAS_SYSTEM_NULLPTR_HPP

#if __cplusplus > 199711L
  #define fas_nullptr nullptr  
  #define fas_nullptr_t nullptr_t
#else
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
