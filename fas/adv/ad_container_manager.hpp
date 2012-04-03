#ifndef FAS_ADV_AD_CONTAINER_MANAGER_HPP
#define FAS_ADV_AD_CONTAINER_MANAGER_HPP

#include <fas/range/range.hpp>

namespace fas{

// TODO: сделать для массива и динамического выделения

template<typename Tg, size_t R = 32, size_t MR = 1024 >
struct ad_container_manager
{
  template<typename T>
  struct container_type_t
  {
    typedef typename T::aspect::template advice_cast<Tg>::type type;
  };

  template<typename T>
  struct range_type_t
  {
    typedef typename container_type_t<T>::type container_type;
    typedef typename typerange< container_type >::range type;
  };

  template<typename T>
  struct init_range_type_t
  {
    typedef typename container_type_t<T>::type container_type;
    typedef typename typerange< container_type >::init_range type;
  };
  

  template<typename T>
  void initialize(T& t)
  {
    t.get_aspect().template get<Tg>().reserve(R);
  }

  template<typename T>
  void clear(T& t)
  {
    if (t.get_aspect().template get<Tg>().capacity() < MR )
      t.get_aspect().template get<Tg>().clear();
    else
    {
      typedef typename T::aspect::template advice_cast<Tg>::type container_type;
      container_type().swap( t.get_aspect().template get<Tg>() );
      t.get_aspect().template get<Tg>().reserve(MR);
    }
  }

  template<typename T>
  void dispose(T& t)
  {
    typedef typename T::aspect::template advice_cast<Tg>::type container_type;
    container_type().swap( t.get_aspect().template get<Tg>() );
  }
  
  template<typename T>
  typename range_type_t<T>::type
  range(T& t)
  {
    return ::fas::range( t.get_aspect().template get<Tg>() );
  }

  template<typename T>
  typename init_range_type_t<T>::type
  init_range(T& t)
  {
    return ::fas::init_range( t.get_aspect().template get<Tg>() );
  }
  
  template<typename T>
  typename container_type_t<T>::type& container(T& t)
  {
    return t.get_aspect().template get<Tg>();
  }

};

}

#endif

