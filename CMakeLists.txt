cmake_minimum_required(VERSION 3.10)

project(TicTacToe)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT EXISTS "${CMAKE_SOURCE_DIR}/vcpkg")
    message(STATUS "vcpkg не найден. Загружаем vcpkg...")
    execute_process(
        COMMAND git clone https://github.com/microsoft/vcpkg.git
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    )
    execute_process(
        COMMAND ${CMAKE_SOURCE_DIR}/vcpkg/bootstrap-vcpkg.bat
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/vcpkg
    )
endif()

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

find_package(Boost REQUIRED)
find_package(Boost COMPONENTS system thread REQUIRED)

set(SERVER_SOURCE_FILES
    Server.cpp
    Game.cpp
    Game.h
)

set(CLIENT_SOURCE_FILES
    Client.cpp
)

add_executable(Server ${SERVER_SOURCE_FILES})
target_link_libraries(Server Boost::Boost Boost::system Boost::thread)

add_executable(Client ${CLIENT_SOURCE_FILES})
target_link_libraries(Client Boost::Boost Boost::system Boost::thread)
