SET(CMAKE_CXX_FLAGS "-Wall -O3 -DHAVE_CONFIG_H")


find_package(Protobuf)

# SET(PROTOBUF_INCLUDE "/home/migashko/distr/protobuf-2.4.1/src/")

if (PROTOBUF_FOUND)
include_directories( ${PROTOBUF_INCLUDE_DIR} )
add_executable(protobuf_s protobuf_s.cpp test1.pb.cc )
add_executable(protobuf_si protobuf_si.cpp test1.pb.cc )
add_executable(protobuf_d protobuf_d.cpp test1.pb.cc )
add_executable(protobuf_di protobuf_di.cpp test1.pb.cc )

add_executable(fasproto_sa fasproto_sa.cpp test1.pb.cc)
add_executable(fasproto_so fasproto_so.cpp test1.pb.cc)
add_executable(fasproto_da fasproto_da.cpp test1.pb.cc)
add_executable(fasproto_do fasproto_do.cpp test1.pb.cc)

endif (PROTOBUF_FOUND)


add_executable(fasjson1_sa fasjson1_sa.cpp )
add_executable(fasjson1_so fasjson1_so.cpp )
add_executable(fasjson1_da fasjson1_da.cpp )
add_executable(fasjson1_do fasjson1_do.cpp )

add_executable(fasjson2_sa fasjson2_sa.cpp )
add_executable(fasjson2_so fasjson2_so.cpp )
add_executable(fasjson2_da fasjson2_da.cpp )
add_executable(fasjson2_do fasjson2_do.cpp )

add_executable(fasjson2p_sa fasjson2p_sa.cpp )
add_executable(fasjson2p_so fasjson2p_so.cpp )
add_executable(fasjson2p_da fasjson2p_da.cpp )
add_executable(fasjson2p_do fasjson2p_do.cpp )


#add_executable(fasjson2ser_p fasjson2ser_p.cpp )


add_executable(sprintf_sa sprintf_sa.cpp )
add_executable(sprintf_so sprintf_so.cpp )
add_executable(sprintf_da sprintf_da.cpp )
add_executable(sprintf_do sprintf_do.cpp )

add_executable(stringstream_sa stringstream_sa.cpp )
add_executable(stringstream_so stringstream_so.cpp )
add_executable(stringstream_da stringstream_da.cpp )
add_executable(stringstream_do stringstream_do.cpp )

add_executable(jsonspirit_s jsonspirit_s.cpp)
add_executable(jsonspirit_si jsonspirit_si.cpp)
add_executable(jsonspirit_d jsonspirit_d.cpp)
add_executable(jsonspirit_di jsonspirit_di.cpp)

add_executable(jsoncpp_s jsoncpp_s.cpp jsoncpp/src/json_writer.cpp jsoncpp/src/json_value.cpp)
add_executable(jsoncpp_si jsoncpp_si.cpp jsoncpp/src/json_writer.cpp jsoncpp/src/json_value.cpp)
add_executable(jsoncpp_d jsoncpp_d.cpp jsoncpp/src/json_reader.cpp jsoncpp/src/json_value.cpp jsoncpp/src/json_writer.cpp)
add_executable(jsoncpp_di jsoncpp_di.cpp jsoncpp/src/json_reader.cpp jsoncpp/src/json_value.cpp jsoncpp/src/json_writer.cpp)

include_directories( jsoncpp )

if (PROTOBUF_FOUND)
target_link_libraries(protobuf_s z pthread ${PROTOBUF_LIBRARY})
target_link_libraries(protobuf_si z pthread ${PROTOBUF_LIBRARY})
target_link_libraries(protobuf_d z pthread ${PROTOBUF_LIBRARY})
target_link_libraries(protobuf_di z pthread ${PROTOBUF_LIBRARY})

target_link_libraries(fasproto_sa z pthread ${PROTOBUF_LIBRARY})
target_link_libraries(fasproto_so z pthread ${PROTOBUF_LIBRARY})
target_link_libraries(fasproto_da z pthread ${PROTOBUF_LIBRARY})
target_link_libraries(fasproto_do z pthread ${PROTOBUF_LIBRARY})
endif(PROTOBUF_FOUND)

if (HAVE_RT_LIB AND FAS_USE_RT_LIB)
  if (PROTOBUF_FOUND)
    target_link_libraries(protobuf_s rt)
    target_link_libraries(protobuf_si rt)
    target_link_libraries(protobuf_d rt)
    target_link_libraries(protobuf_di rt)
    target_link_libraries(fasproto_sa rt)
    target_link_libraries(fasproto_so rt)
    target_link_libraries(fasproto_da rt)
    target_link_libraries(fasproto_do rt)
  endif(PROTOBUF_FOUND)

  target_link_libraries(fasjson1_sa rt)
  target_link_libraries(fasjson1_so rt)
  target_link_libraries(fasjson1_da rt)
  target_link_libraries(fasjson1_do rt)
  
  target_link_libraries(fasjson2_sa rt)
  target_link_libraries(fasjson2_so rt)
  target_link_libraries(fasjson2_da rt)
  target_link_libraries(fasjson2_do rt)

  target_link_libraries(fasjson2p_sa rt)
  target_link_libraries(fasjson2p_so rt)
  target_link_libraries(fasjson2p_da rt)
  target_link_libraries(fasjson2p_do rt)
  

  target_link_libraries(sprintf_sa rt)
  target_link_libraries(sprintf_so rt)
  target_link_libraries(sprintf_da rt)
  target_link_libraries(sprintf_do rt)

  target_link_libraries(stringstream_sa rt)
  target_link_libraries(stringstream_so rt)
  target_link_libraries(stringstream_da rt)
  target_link_libraries(stringstream_do rt)

  target_link_libraries(jsonspirit_s rt)
  target_link_libraries(jsonspirit_si rt)
  target_link_libraries(jsonspirit_d rt)
  target_link_libraries(jsonspirit_di rt)
  target_link_libraries(jsoncpp_s rt)
  target_link_libraries(jsoncpp_si rt)
  target_link_libraries(jsoncpp_d rt)
  target_link_libraries(jsoncpp_di rt)
endif (HAVE_RT_LIB AND FAS_USE_RT_LIB)

add_custom_command(
    TARGET fasjson1_sa
    POST_BUILD
    COMMAND copy ARGS 
    ${CMAKE_CURRENT_SOURCE_DIR}/benchmark.sh
    ${CMAKE_CURRENT_BINARY_DIR}

)
