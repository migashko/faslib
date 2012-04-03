#ifndef FAS_RANGE_ITERATOR2RANGE_HPP
#define FAS_RANGE_ITERATOR2RANGE_HPP

#include <fas/range/output_range.hpp>
#include <fas/range/input_range.hpp>
#include <fas/range/forward_range.hpp>
#include <fas/range/bidirectional_range.hpp>
#include <fas/range/random_access_range.hpp>

#include <fas/typemanip/empty_type.hpp>

#include <iterator>

namespace fas{

template<typename T, typename Tg = empty_type>
struct iterator2range;

template<typename T>
struct iterator2range<T, empty_type>
  : iterator2range<T, typename std::iterator_traits<T>::iterator_category > 
{
};

template<typename T>
struct iterator2range<T, std::input_iterator_tag>
{
  typedef input_range<T> type;
};

template<typename T>
struct iterator2range<T, std::output_iterator_tag>
{
  typedef output_range<T> type;
};

template<typename T>
struct iterator2range<T, std::forward_iterator_tag>
{
  typedef forward_range<T> type;
};

template<typename T>
struct iterator2range<T, std::bidirectional_iterator_tag>
{
  typedef bidirectional_range<T> type;
};

template<typename T>
struct iterator2range<T, std::random_access_iterator_tag>
{
  typedef random_access_range<T> type;
};

};

#endif
