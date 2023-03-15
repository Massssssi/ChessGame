cmake_minimum_required(VERSION 3.5)

project(ChessGame)


if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MD")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MDd")
endif()



add_executable(ChessProgram
	src/main.cpp 
	src/user.cpp
	src/users.cpp
	src/board.cpp
	src/piece.cpp
	src/move.cpp
	src/position.cpp
	include/user.h
	include/users.h
	include/board.h
	include/piece.h
	include/move.h
	include/position.h
)

target_include_directories(ChessProgram PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/include)


install(TARGETS ChessProgram
  DESTINATION lib/${PROJECT_NAME})

# Enable testing for the project
enable_testing()
set(gtest_force_shared_crt ON CACHE BOOL "Use shared (DLL) run-time lib even when Google Test is built as static lib" )

# Add GoogleTest
add_subdirectory(third_party/googletest-main)

# Declare a C++ executable
add_executable(tests 
	  tests/tests.cpp)

# Link against gtest_main
target_link_libraries(tests gtest_main)

# Include tests
include(GoogleTest)
gtest_discover_tests(tests)