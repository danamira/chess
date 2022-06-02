
set(CMAKE_CXX_COMPILER "C:/MinGW/bin")
set(CMAKE_C_COMPILER "C:/MinGW/bin")

cmake_minimum_required(VERSION 3.1.0)

project(Chess)
set(CMAKE_CXX_STANDARD 11)

set(SRC_DIRECTORY src)
set(INCLUDE_DIRECTORY headers)
set(SOURCES
    ${SRC_DIRECTORY/Piece.cpp}
    ${SRC_DIRECTORY/Board.cpp}
    ${SRC_DIRECTORY/Calc.cpp}
    ${SRC_DIRECTORY/Main.cpp}
)
include_directories(${INCLUDE_DIRECTORY})
add_executable(${PROJECT_NAME} ${SRC_DIRECTORY}/Main.cpp ${SOURCES})