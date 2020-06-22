cmake_minimum_required(VERSION 3.16)
project(jwtclivalidation)

set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_COMPILER_ARG1 "-v")
add_executable(jwtclivalidation main.cpp)

include_directories(./include)

if (APPLE)
    list(PREPEND CMAKE_PREFIX_PATH /usr/local/opt/openssl@1.1)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(Ssl IMPORTED_TARGET openssl)
    target_link_libraries(${PROJECT_NAME} PkgConfig::Ssl)
else()
    find_package(OpenSSL REQUIRED)
    include_directories(SYSTEM ${OPENSSL_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${OPENSSL_LIBRARIES})
endif()