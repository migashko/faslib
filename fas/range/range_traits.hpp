#ifndef FAS_RANGE_RANGE_TRAITS_HPP
#define FAS_RANGE_RANGE_TRAITS_HPP

#include <iterator>
#include <fas/range/range_category.hpp>
namespace fas{

template< typename R>
struct range_traits
{
  typedef typename R::iterator iterator;
  typedef typename R::range_category    range_category;
  typedef typename R::iterator_category iterator_category;
  typedef typename R::value_type        value_type;
  typedef typename R::difference_type   difference_type;
  typedef typename R::pointer           pointer;
  typedef typename R::reference         reference;
};

template< typename T>
struct range_traits<T*>
{
  typedef T*                         iterator;
  typedef random_access_range_tag    range_category;
  typedef std::random_access_iterator_tag
                                     iterator_category;
  typedef T                          value_type;
  typedef std::ptrdiff_t             difference_type;
  typedef T*                         pointer;
  typedef T&                         reference;
};

};

#endif
