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
find_package(asio REQUIRED)
#find_package(Boost REQUIRED)

add_executable(client)
target_include_directories(client PUBLIC includes )
set(SOURCES
    src/client.cpp
    src/style.cpp
    src/defs.cpp

    )

target_sources(client PRIVATE ${SOURCES})

target_link_libraries(client PRIVATE fmt::fmt OpenSSL::SSL OpenSSL::Crypto  asio::asio )
target_compile_features(client PUBLIC cxx_std_20)
target_compile_options(client PUBLIC -Wall --std=c++20)#-fno-exceptions 


add_executable(server)
target_include_directories(server PUBLIC includes )
set(SOURCES
    src/server.cpp
    src/style.cpp
    src/defs.cpp

    )

target_sources(server PRIVATE ${SOURCES})

target_link_libraries(server PRIVATE fmt::fmt OpenSSL::SSL OpenSSL::Crypto  asio::asio)
target_compile_features(server PUBLIC cxx_std_20)
target_compile_options(server PUBLIC -Wall -fno-exceptions --std=c++20)

# target_link_libraries(server PRIVATE fmt::fmt)
