cmake_minimum_required(VERSION 3.0)
project(Castorama)

# Find the sqlite3 library
find_package(SQLite3 REQUIRED)
find_library(SQLITE3_LIBRARY sqlite3)

set(CMAKE_CXX_STANDARD 17)

add_executable(Castorama main.cpp)

# Link your target with the sqlite3 library
target_link_libraries(Castorama -lsqlite3)