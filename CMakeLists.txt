cmake_minimum_required(VERSION 3.22)

project(Screenwriter VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_standard_project_setup()

qt_add_executable(Screenwriter
    src/main.cpp
    src/ui/MainWindow.cpp
)

target_include_directories(Screenwriter PRIVATE
    src
    src/ui
)

target_link_libraries(Screenwriter PRIVATE
    Qt6::Widgets
)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(Screenwriter PRIVATE
        -Wall
        -Wextra
        -Wpedantic
    )
endif()
