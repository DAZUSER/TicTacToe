cmake_minimum_required(VERSION 3.10)

project(TicTacToe)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

find_package(Boost REQUIRED)

set(SERVER_SOURCE_FILES
    Server.cpp
    Game.cpp
    Game.h
)

set(CLIENT_SOURCE_FILES
    Client.cpp
    Game.cpp
    Game.h
)

add_executable(Server ${SERVER_SOURCE_FILES})
target_link_libraries(Server Boost::Boost boost_system boost_thread)

add_executable(Client ${CLIENT_SOURCE_FILES})
target_link_libraries(Client Boost::Boost boost_system boost_thread)
