#ifndef FAS_RANGE_RANGE_CATEGORY_HPP
#define FAS_RANGE_RANGE_CATEGORY_HPP

namespace fas{

struct trivial_range_tag { };

struct input_range_tag { };

struct output_range_tag { };

struct forward_range_tag : public input_range_tag { };

struct bidirectional_range_tag : public forward_range_tag { };

struct random_access_range_tag : public bidirectional_range_tag { };

}

#endif
