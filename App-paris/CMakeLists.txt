cmake_minimum_required(VERSION 3.21)
project(App-paris C)

set(CMAKE_C_STANDARD 99)

include_directories("C:/API-C-lib/mysql-8.0.27-winx64/include")
include_directories("C:/API-C-lib/curl-7.80.0-win64-mingw/include")

add_library(libmysql SHARED IMPORTED)
add_library(libcurl SHARED IMPORTED)



set_target_properties(
        libmysql
        PROPERTIES LINKER_LANGUAGE C
        IMPORTED_IMPLIB "C:/API-C-lib/mysql-8.0.27-winx64/lib/libmysql.lib"
)
set_target_properties(
        libcurl
        PROPERTIES LINKER_LANGUAGE C
        IMPORTED_IMPLIB "C:/API-C-lib/curl-7.80.0-win64-mingw/lib/libcurl.dll.a"
)

link_libraries("C:/API-C-lib/mysql-8.0.27-winx64/lib")
link_libraries("C:/API-C-lib/curl-7.80.0-win64-mingw/lib")

add_executable(App-paris main.c)
target_link_libraries(App-paris libmysql)
target_link_libraries(App-paris libcurl)
