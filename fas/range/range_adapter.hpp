//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2012
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_RANGE_RANGE_ADAPTER_HPP
#define FAS_RANGE_RANGE_ADAPTER_HPP

#include <fas/range/typerange.hpp>
#include <fas/range/orange.hpp>
#include <fas/range/range.hpp>
#include <fas/range/distance.hpp>
#include <vector>

namespace fas {

template<
  typename InputRange,
  typename Container = std::vector<typename InputRange::value_type>
>
class input_range_adapter
{
  typedef InputRange  input_range;
  typedef Container   container;
  typedef typename typerange<container>::orange output_range;
  typedef typename typerange<container>::range container_range;
public:
  
  typedef typename container_range::range_category   range_category;
  typedef typename container_range::iterator         iterator;
  typedef typename container_range::reverse_iterator reverse_iterator;
  typedef typename container_range::reverse_range    reverse_range;
  
  typedef typename container_range::iterator_category iterator_category;
  typedef typename container_range::value_type        value_type;
  typedef typename container_range::difference_type   difference_type;
  typedef typename container_range::pointer           pointer;
  typedef typename container_range::reference         reference;
  

  input_range_adapter(input_range r, container& c)
    : _input_range(r)
    , _container(&c)
    , _output_range( orange(c) )
    , _pos(-1)
  {
    if ( _input_range )
    {
      *(_output_range++) = *_input_range;
      _pos=0;
    }
  }

  operator input_range () const { return  _input_range; }

  operator bool () const {  return _pos < static_cast<difference_type>(_container->size()); }

  reference operator*() const { return (*_container)[_pos]; }

  pointer operator ->() const  { return &( (*_container)[_pos] );}

  iterator begin() const { return _container->begin() + _pos; }

  iterator end() const { return _container->end(); }

  difference_type distance() const { return static_cast<difference_type>(_container->size()); }

  void advance(difference_type s)
  {
    std::advance(*this, s);
  }

  input_range_adapter<InputRange, Container>& operator++()
  {
    ++_input_range;
    ++_pos;
    if (_input_range)
      *(_output_range++) = *(_input_range);
    return *this;
  }

  input_range_adapter<InputRange, Container> operator++(int)
  {
    input_range_adapter<InputRange, Container> ans = *this;
    ++_input_range;
    ++_pos;
    if (_input_range)
      *(_output_range++) = *(_input_range);
    return ans;
  }

  bool operator == (const input_range_adapter<InputRange, Container>& r ) const { return _input_range.operator==(r._input_range) && _pos == r._pos; }

  bool operator != (const input_range_adapter<InputRange, Container>& r ) const { return !(*this == r); }

  
private:
  input_range      _input_range;
  container*       _container;
  output_range     _output_range;
  //container_range  _range;
  difference_type  _pos;
};


template<
  typename InputRange,
  typename OutputRange
>
class copy_range_adapter
{
  typedef InputRange   input_range;
  typedef OutputRange  output_range;

public:

  typedef typename input_range::range_category   range_category;
  typedef typename input_range::iterator         iterator;

  typedef typename input_range::iterator_category iterator_category;
  typedef typename input_range::value_type        value_type;
  typedef typename input_range::difference_type   difference_type;
  typedef typename input_range::pointer           pointer;
  typedef typename input_range::reference         reference;


  copy_range_adapter(input_range ri, output_range ro)
    : _input_range(ri)
    , _output_range(ro)
  {
  }

  operator input_range () const  { return  _input_range; }
  operator output_range () const { return  _output_range; }

  operator bool () const {  return _input_range; }

  reference operator*() const { return *_input_range; }

  pointer operator ->() const { return &( *_input_range );}

  iterator begin() const { return _input_range->begin(); }

  iterator end() const { return _input_range->end(); }

  difference_type distance() const { return ::fas::distance(_input_range); }

  /*void advance(difference_type s)  {
    _input_range->advance(s);
  }
  */

  copy_range_adapter<InputRange, OutputRange>& operator++()
  {
    *(_output_range++) = *(_input_range++);
    return *this;
  }

  copy_range_adapter<InputRange, OutputRange> operator++(int)
  {
    copy_range_adapter<InputRange, OutputRange> ans = *this;
    *(_output_range++) = *(_input_range++);
    return ans;
  }

  bool operator == (const copy_range_adapter<InputRange, OutputRange>& r ) const { return _input_range.operator==(r._input_range); }

  bool operator != (const copy_range_adapter<InputRange, OutputRange>& r ) const { return !(*this == r); }


private:
  input_range      _input_range;
  output_range     _output_range;
};

}

#endif
