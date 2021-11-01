include(FetchContent)

cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(example-app)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")
set(CMAKE_CXX_STANDARD 17)


message(Install dependencies)

find_package(Torch REQUIRED)
FetchContent_Declare(
        json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG v3.7.3
)
FetchContent_GetProperties(json)
if(NOT json_POPULATED)
    FetchContent_Populate(json)
    add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)




message(Build library)

add_library(example-app-lib src/models/banner.h src/models/utils.h src/models/hit.h src/models/banner.cpp src/models/utils.cpp src/models/hit.cpp src/service/service.h src/service/service.cpp http/httplib.h src/service/server.h)
target_link_libraries(example-app-lib "${TORCH_LIBRARIES}" nlohmann_json::nlohmann_json)




message(Build executable service)

add_executable(example-app src/main.cpp)
target_link_libraries(example-app example-app-lib)
set_property(TARGET example-app PROPERTY CXX_STANDARD 17)




# message(Build tests)

# enable_testing()

# add_executable(
#     example-app-test
#     tests/torch_example.cpp
#     tests/hit.cpp
#     tests/banner.cpp
#     tests/service.cpp
# )
# target_link_libraries(
#     example-app-test
#     gtest_main
#     example-app-lib
# )
# set_property(TARGET example-app-test PROPERTY CXX_STANDARD 17)

# include(GoogleTest)
# gtest_discover_tests(example-app-test)
