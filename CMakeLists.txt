cmake_minimum_required(VERSION 3.5)

project(ChessGame)

set(CMAKE_CXX_STANDARD 17)

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