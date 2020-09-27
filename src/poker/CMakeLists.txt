set(targetName poker)

set(srcList
        Card.cpp
        Card.h
        Suit.h
        Hand.cpp
        Hand.h)

add_library(${targetName} STATIC ${srcList})
add_dependencies(${targetName} ${DEP_PROJECTS})
target_include_directories(${targetName} PUBLIC ${DEP_INSTALL_DIR}/include)
target_include_directories(${targetName} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

unset(${targetName})