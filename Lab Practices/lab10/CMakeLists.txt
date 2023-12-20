cmake_minimum_required(VERSION 3.10)

project(lab10)

aux_source_directory(. DIRS)

add_executable(lab10p ${DIRS})

include_directories(./include)

add_subdirectory(./liba)

add_subdirectory(./libs)

target_link_libraries(lab10p MYLIBA MYLIBS)