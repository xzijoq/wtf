cmake_minimum_required(VERSION 3.2)

project(template)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR} ./conan_cmake)
set(CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR} ./conan_cmake)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/conan_cmake)


find_package(fmt REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(asio REQUIRED)
find_package(Backward REQUIRED)
# find_package(libdwarf REQUIRED) find_package(Boost REQUIRED)
set(OPENSSL_USE_STATIC_LIBS TRUE)

set(CommonLib
    fmt::fmt
    OpenSSL::SSL
    OpenSSL::Crypto
    asio::asio
    Backward::Backward
    unwind
    dwarf)

set(CommonSrc src/style.cpp src/defs.cpp src/backward.cpp)

set(CommonFlg -Wall --std=c++20 -g)

message(STATUS ${CommonLib})
message(STATUS ${CommonSrc})

# ------------CLIENT
add_executable(client)
set(SOURCES src/client.cpp ${CommonSrc})

target_include_directories(client PUBLIC includes)
#target_precompile_headers(client PUBLIC includes/defs.h)
target_sources(client PRIVATE ${SOURCES})
target_link_libraries(client PRIVATE ${CommonLib})

target_compile_features(client PUBLIC cxx_std_20)
target_compile_options(client PUBLIC ${CommonFlg}) # -fno-exceptions
# ----------END CLIENT
#
# ---------SERVER
add_executable(server)
set(SOURCES src/server.cpp ${CommonSrc})

target_include_directories(server PUBLIC includes)
#target_precompile_headers(server PUBLIC includes/defs.h)
target_sources(server PRIVATE ${SOURCES})
target_link_libraries(server PRIVATE ${CommonLib})

target_compile_features(server PUBLIC cxx_std_20)
target_compile_options(server PUBLIC ${CommonFlg})
# -------------END SERVER target_link_libraries(server PRIVATE fmt::fmt)
