cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(barkeshli_s22 LANGUAGES CXX)

include(GNUInstallDirs)
include(FetchContent)

if(MSVC)
    add_compile_options(/W4)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin)
else()
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
endif()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    # if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    #     add_compile_options("-fprofile-arcs" "-ftest-coverage")
    #     add_link_options("-fprofile-arcs" "-ftest-coverage")
    # endif()
endif()

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
#   Grab all cpp files from includes folder
#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
set(INCLUDES_FOLDER includes)
FILE(GLOB_RECURSE SOURCE_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}   "${INCLUDES_FOLDER}/*.cpp" )
#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 


# --------------------- GTest Setup ---------------------
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.17.0
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(INSTALL_GTEST OFF CACHE BOOL "Disable installation of googletest" FORCE)

FetchContent_MakeAvailable(googletest)
enable_testing()

# --------------------- SFML Setup ---------------------
FetchContent_Declare(
    sfml
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG        2.6.2
)

FetchContent_MakeAvailable(sfml)

# --------------------- Executables ---------------------
add_executable(main
    main.cpp
    ${SOURCE_FILES}
)

target_include_directories(main PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/includes)
target_link_libraries(main PRIVATE)

add_executable(basic_test
    _tests/_test_files/basic_test.cpp
)

target_include_directories(basic_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/includes)
target_link_libraries(basic_test PRIVATE GTest::gtest GTest::gtest_main)

add_executable(testB
    _tests/_test_files/testB.cpp
)

target_include_directories(testB PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/includes)
target_link_libraries(testB PRIVATE GTest::gtest GTest::gtest_main)

# --------------------- Google Test Discovery ---------------------
include(GoogleTest)
gtest_discover_tests(basic_test)
gtest_discover_tests(testB)
