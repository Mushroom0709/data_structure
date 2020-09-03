cmake_minimum_required (VERSION 3.8)

add_library(x_library_socket SHARED
 "src/x_library_socket_base.cpp"
 "src/x_library_server_epoll.cpp"
 "src/x_library_server_select.cpp"
 "src/x_library_socket_tcp_server.cpp"
 "src/x_library_connect_select.cpp"
 "src/x_library_socket_tcp_connect.cpp")

target_link_libraries(x_library_socket  pthread)