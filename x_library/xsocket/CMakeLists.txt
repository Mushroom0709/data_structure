cmake_minimum_required (VERSION 3.8)

add_library(x_library_socket SHARED
"src/x_library_socket_base.cpp"
"src/x_library_socket_epoll.cpp"
"src/x_library_socket_select.cpp"
)

target_link_libraries(x_library_socket  pthread)