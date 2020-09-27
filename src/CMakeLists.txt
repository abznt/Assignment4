set(targetName main)

include(${CMAKE_SOURCE_DIR}/cmake/Dependency.cmake)

find_package(libconfig++ REQUIRED)
get_target_property(LIBCONFIG_DLL libconfig::libconfig++ IMPORTED_LOCATION_DEBUG)

add_subdirectory(statistics)
add_subdirectory(utils)
add_subdirectory(poker)

add_executable(${targetName} main.cpp)
add_dependencies(${targetName} ${DEP_PROJECTS})
target_include_directories(${targetName} PUBLIC ${DEP_INSTALL_DIR}/include)
target_link_libraries(${targetName} libconfig::libconfig++)
target_link_libraries(${targetName} poker)
target_link_libraries(${targetName} Statistics)
target_link_libraries(${targetName} Utils)

install(TARGETS ${targetName} DESTINATION ${CMAKE_BINARY_DIR}/bin)
add_custom_command(TARGET ${targetName} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${LIBCONFIG_DLL} ${CMAKE_BINARY_DIR}/bin)
configure_file(${CMAKE_SOURCE_DIR}/input/assignment4.cfg ${CMAKE_BINARY_DIR}/input COPYONLY)

unset(targetName)