cmake_minimum_required(VERSION 3.2)

project(template)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR} ./conan_cmake)
# message(WARNING "PATH IS ${CMAKE_PREFIX_PATH}")
set(CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR} ./conan_cmake)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/conan_cmake)
set(OPENSSL_USE_STATIC_LIBS TRUE)

find_package(fmt REQUIRED)
find_package(OpenSSL REQUIRED)

add_executable(t1)
target_include_directories(t1 PRIVATE includes bindings)
set(SOURCES
    src/main.cpp
    src/style.cpp

    )

target_sources(t1 PRIVATE ${SOURCES})

target_link_libraries(t1 PRIVATE fmt::fmt OpenSSL::Crypto )

# target_link_libraries(t1 PRIVATE fmt::fmt)
