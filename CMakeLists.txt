cmake_minimum_required(VERSION 3.0)
project(Castorama)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_PREFIX_PATH "~/sdk_build/lib")

add_executable(Castorama main.cpp CRequest.cpp CRequest.h CDataBase.cpp CDataBase.h)

option(BUILD_SHARED_LIBS "Build shared libraries" ON)
find_package(AWSSDK REQUIRED COMPONENTS core dynamodb)
target_compile_features(Castorama PUBLIC cxx_std_11)
target_link_libraries(Castorama ${AWSSDK_LINK_LIBRARIES})