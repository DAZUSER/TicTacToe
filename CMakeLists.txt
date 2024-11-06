cmake_minimum_required(VERSION 3.10)

project(TicTacToe)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Проверка и автоматическая установка vcpkg
if(NOT EXISTS "${CMAKE_SOURCE_DIR}/vcpkg")
    message(STATUS "vcpkg не найден. Загружаем vcpkg...")
    execute_process(
        COMMAND git clone https://github.com/microsoft/vcpkg.git
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    )
    if(WIN32)
        execute_process(
            COMMAND ${CMAKE_SOURCE_DIR}/vcpkg/bootstrap-vcpkg.bat
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/vcpkg
        )
    else()
        execute_process(
            COMMAND ${CMAKE_SOURCE_DIR}/vcpkg/bootstrap-vcpkg.sh
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/vcpkg
        )
    endif()
endif()

# Указание пути к toolchain файлу vcpkg
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

# Подключение необходимых библиотек через vcpkg
find_package(Boost REQUIRED COMPONENTS system thread)

# Источники для сервера
set(SERVER_SOURCE_FILES
    Server.cpp
    Game.cpp
    Game.h
)

# Источники для клиента
set(CLIENT_SOURCE_FILES
    Client.cpp
)

# Создание исполняемого файла для сервера
add_executable(Server ${SERVER_SOURCE_FILES})
target_link_libraries(Server Boost::Boost Boost::system Boost::thread)

# Создание исполняемого файла для клиента
add_executable(Client ${CLIENT_SOURCE_FILES})
target_link_libraries(Client Boost::Boost Boost::system Boost::thread)
