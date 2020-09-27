include(ExternalProject)

set(DEP_INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}/Dependency)
set(DEP_PROJECTS dep_spdlog)

ExternalProject_Add(
        dep_spdlog
        GIT_REPOSITORY "https://github.com/gabime/spdlog"
        GIT_TAG "v1.x"
        GIT_SHALLOW 1
        UPDATE_COMMAND ""
        PATCH_COMMAND ""
        CMAKE_ARGS
        -DCMAKE_INSTALL_PREFIX=${DEP_INSTALL_DIR}
        -DSPDLOG_BUILD_EXAMPLES=OFF
        -DSPDLOG_BUILD_BENCH=OFF
        -DSPDLOG_BUILD_TESTS=OFF
        TEST_COMMAND ""
)

