cmake_minimum_required(VERSION 3.16.3)

#Nome no projeto
project(api-dados)

set(CMAKE_CXX_STANDARD 11)

#pastas de arquivos src
file(GLOB SOURCES

    sources/*.cpp
    
)

add_executable(api-dados ${SOURCES})

#pasta dos arquivos headers
target_include_directories(api-dados PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} / headers)

