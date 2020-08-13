cmake_minimum_required (VERSION 3.8)

add_library(x_library_redis_base SHARED
"src/x_library_redis_base.cpp")

add_library(x_library_redis SHARED
"src/x_library_redis.cpp")

target_link_libraries(x_library_redis_base hiredis)
target_link_libraries(x_library_redis x_library_redis_base)