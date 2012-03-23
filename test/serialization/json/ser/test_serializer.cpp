#include <fas/testing.hpp>

BEGIN_TEST
  RUN_SUITE(number_serializer_suite)
  RUN_SUITE(string_serializer_suite)
  RUN_SUITE(enumeration_serialize_suite)
  RUN_SUITE(sequence_serializer_suite)
  RUN_SUITE(field_serialize_suite)
  RUN_SUITE(field_list_serialize_suite)
  RUN_SUITE(member_serialize_suite)
  RUN_SUITE(member_list_serialize_suite)
  RUN_SUITE(array_serializer_suite)
  RUN_SUITE(object_serializer_suite)
  RUN_SUITE(formatting_serialize_suite)
  RUN_SUITE(raw_serializer_suite)
  RUN_SUITE(serializer_suite)  
END_TEST
