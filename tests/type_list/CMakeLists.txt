add_executable(test_type_list       test_type_list.cpp)
add_executable(test_check_organized test_check_organized.cpp)
add_executable(test_length          test_length.cpp)
add_executable(test_type_count      test_type_count.cpp)
add_executable(test_type_at         test_type_at.cpp)
add_executable(test_index_of        test_index_of.cpp)
add_executable(test_merge           test_merge.cpp)
add_executable(test_organize        test_organize.cpp)
add_executable(test_split           test_split.cpp)
add_executable(test_erase           test_erase.cpp)
add_executable(test_reverse         test_reverse.cpp)
add_executable(test_push_front      test_push_front.cpp)
add_executable(test_push_back       test_push_back.cpp)
add_executable(test_unique          test_unique.cpp)
add_executable(test_unique_first    test_unique_first.cpp)

wci_test(NAME type_list                  TARGET test_type_list)
wci_test(NAME type_list_check_organized  TARGET test_check_organized)
wci_test(NAME type_list_length           TARGET test_length)
wci_test(NAME type_list_type_count       TARGET test_type_count)
wci_test(NAME type_list_type_at          TARGET test_type_at)
wci_test(NAME type_list_organize         TARGET test_organize)
wci_test(NAME type_list_merge            TARGET test_merge)
wci_test(NAME type_list_split            TARGET test_split)
wci_test(NAME type_list_erase            TARGET test_erase)
wci_test(NAME type_list_unique           TARGET test_unique)
wci_test(NAME type_list_unique_first     TARGET test_unique_first)
wci_test(NAME type_list_reverse          TARGET test_reverse)
wci_test(NAME type_list_index_of         TARGET test_index_of)
wci_test(NAME type_list_push_front       TARGET test_push_front)
wci_test(NAME type_list_push_back        TARGET test_push_back)

