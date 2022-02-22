cmake_minimum_required(VERSION 3.2)

project(template)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)



set(CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR} ./conan_cmake)
# message(WARNING "PATH IS ${CMAKE_PREFIX_PATH}")
set(CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR} ./conan_cmake)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/conan_cmake)


find_package(fmt REQUIRED)

add_executable(main)
target_include_directories(main PUBLIC includes )
set(SOURCES
    src/main.cpp
    src/style.cpp
    )

target_sources(main PRIVATE ${SOURCES})

target_link_libraries(main PRIVATE fmt::fmt)# OpenSSL::SSL OpenSSL::Crypto  asio::asio )
target_compile_features(main PUBLIC cxx_std_20)
target_compile_options(main PUBLIC  --std=c++20)#-fno-exceptions -Wall


# target_link_libraries(server PRIVATE fmt::fmt)
