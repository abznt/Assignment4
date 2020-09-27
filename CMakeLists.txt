cmake_minimum_required(VERSION 3.17)
project(Assignment4)

set(CMAKE_CXX_STANDARD 17)
set(doxy_main_page ${PROJECT_SOURCE_DIR}/README.md)

add_subdirectory(src)
add_subdirectory(docs)
add_subdirectory(tests)

#file(COPY input DESTINATION ${CMAKE_CURRENT_BINARY_DIR})