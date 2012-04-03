#ifndef FAS_RANGE_RANGE_TRAITS_HPP
#define FAS_RANGE_RANGE_TRAITS_HPP

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

};

#endif
