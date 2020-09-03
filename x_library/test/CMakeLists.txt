cmake_minimum_required (VERSION 3.8)

add_executable(xredis_test  "xredis_test.cpp")

add_executable(xcommon_test  "xcommon_test.cpp")

add_executable(xsocket_server_test  "xsocket_server_test.cpp")

add_executable(xsocket_connect_test  "xsocket_connect_test.cpp")

target_link_libraries(xredis_test x_library_redis)
target_link_libraries(xsocket_server_test x_library_socket)
target_link_libraries(xsocket_connect_test x_library_socket)