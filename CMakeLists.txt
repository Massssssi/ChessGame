cmake_minimum_required(VERSION 3.5)

project(ChessGame)

add_executable(ChessProgram src/main.cpp src/user.cpp src/users.cpp include/user.h include/users.h)

target_include_directories(ChessProgram PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/include)


install(TARGETS ChessProgram
  DESTINATION lib/${PROJECT_NAME})