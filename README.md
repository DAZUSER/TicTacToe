Readme 1.0.0
Игра Крестики-Нолики
Эта игра представляет собой клиент-серверное приложение для игры в крестики-нолики, написанное на C++ с использованием Boost.Asio для работы с сетью.
Предварительные требования
* CMake 3.10 или новее
* Git
* Компилятор C++17
    * Windows: Visual Studio 2019 или новее
    * macOS: Xcode или GCC (устанавливается через Homebrew)
    * Linux: GCC или Clang
Быстрая установка
Для управления зависимостями (в частности, Boost) в проекте используется vcpkg. Если vcpkg не найден в папке проекта, CMake автоматически загрузит и установит его во время конфигурации.
Установка и запуск
1. Клонирование репозитория
bash
Копировать код
git clone https://github.com/yourusername/tic-tac-toe.git
cd tic-tac-toe
2. Инструкции по сборке и запуску
Windows
1. Откройте Developer Command Prompt for Visual Studio.
2. Выполните команды для конфигурации и сборки проекта: bash Копировать код   cmake -B build -S . -G "Visual Studio 16 2019"
3. cmake --build build --config Release
4.   
5. Для запуска сервера и клиента:
    * Откройте два окна терминала.
    * Запустите сервер:bash Копировать код   .\build\Release\Server.exe
    *   
    * Во втором терминале запустите клиент:bash Копировать код   .\build\Release\Client.exe
    *   
macOS
1. Установите CMake и Boost с помощью Homebrew: bash Копировать код   brew install cmake
2.   
3. Настройте и соберите проект: bash Копировать код   cmake -B build -S .
4. cmake --build build --config Release
5.   
6. Запустите сервер и клиент:
    * Откройте два окна терминала.
    * Запустите сервер:bash Копировать код   ./build/Server
    *   
    * Во втором терминале запустите клиент:bash Копировать код   ./build/Client
    *   
Linux
1. Установите CMake и Boost:
    * Для Debian-подобных систем:bash Копировать код   sudo apt update
    * sudo apt install -y cmake g++ libboost-all-dev
    *   
    * Для систем на базе RedHat:bash Копировать код   sudo yum install -y cmake gcc-c++ boost-devel
    *   
2. Настройте и соберите проект: bash Копировать код   cmake -B build -S .
3. cmake --build build --config Release
4.   
5. Запустите сервер и клиент:
    * Откройте два окна терминала.
    * Запустите сервер:bash Копировать код   ./build/Server
    *   
    * Во втором терминале запустите клиент:bash Копировать код   ./build/Client
    *   
Устранение неполадок
* Если CMake не найден:
    * Windows: Убедитесь, что он добавлен в PATH, или установите через установщик Visual Studio.
    * macOS: Установите CMake через Homebrew (brew install cmake).
    * Linux: Установите CMake с помощью вашего пакетного менеджера.
* Ошибки при установке Boost: Убедитесь, что vcpkg установлен правильно. Если CMake не может автоматически установить vcpkg, попробуйте клонировать его вручную: bash Копировать код   git clone https://github.com/microsoft/vcpkg.git
* ./vcpkg/bootstrap-vcpkg.sh  # Или bootstrap-vcpkg.bat на Windows
*   
Структура проекта
bash
Копировать код
tic-tac-toe/
├── CMakeLists.txt       # Файл конфигурации сборки
├── vcpkg/               # (Загружается автоматически) Менеджер зависимостей для Boost
├── src/                 # Исходные файлы
│   ├── Client.cpp       # Код клиентского приложения
│   ├── Server.cpp       # Код серверного приложения
│   ├── Game.cpp         # Реализация логики игры
│   └── Game.h           # Заголовочный файл логики игры
└── README.md            # Инструкции для проекта

В будущем можно кратно улучшить функционал и совместимость.
