//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2012
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_RANGE_COPY_RANGE_ADAPTER_HPP
#define FAS_RANGE_COPY_RANGE_ADAPTER_HPP

#include <fas/range/typerange.hpp>
#include <fas/range/orange.hpp>
#include <fas/range/range.hpp>
#include <fas/range/distance.hpp>

namespace fas {

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
    if ( _input_range )
      *(_output_range++) = *_input_range;
  }

  operator input_range () const  { return  _input_range; }
  operator output_range () const { return  _output_range; }

  operator bool () const {  return _input_range; }

  reference operator*() const { return *_input_range; }

  pointer operator ->() const { return &( *_input_range );}

  iterator begin() const { return _input_range->begin(); }

  iterator end() const { return _input_range->end(); }

  difference_type distance() const { return ::fas::distance(_input_range); }

  copy_range_adapter<InputRange, OutputRange>& operator++()
  {
    ++_input_range;
    if ( _input_range )
      *(_output_range++) = *_input_range;
    return *this;
  }

  copy_range_adapter<InputRange, OutputRange> operator++(int)
  {
    copy_range_adapter<InputRange, OutputRange> ans = *this;
    ++_input_range;
    if ( _input_range )
      *(_output_range++) = *_input_range;
    return ans;
  }

  bool operator == (const copy_range_adapter<InputRange, OutputRange>& r ) const { return _input_range.operator==(r._input_range); }

  bool operator != (const copy_range_adapter<InputRange, OutputRange>& r ) const { return !(*this == r); }


private:
  input_range      _input_range;
  output_range     _output_range;
  value_type       _value;
};

}

#endif
