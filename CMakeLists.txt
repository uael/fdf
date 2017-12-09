cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
cmake_policy(SET CMP0054 OLD)
cmake_policy(SET CMP0045 OLD)

project(fdf C)
add_subdirectory(libft)

set(BUILD_SHARED_LIBS OFF)

set(fdf_INC_DIR ${CMAKE_CURRENT_LIST_DIR}/include)
set(fdf_SRC_DIR ${CMAKE_CURRENT_LIST_DIR}/src)
set(fdf_TEST_DIR ${CMAKE_CURRENT_LIST_DIR}/test)

set(CMAKE_C_FLAGS "")
set(CMAKE_C_FLAGS_DEBUG "")
set(CMAKE_C_FLAGS_RELEASE "")

set(fdf_HDR ${fdf_INC_DIR}/fdf.h)
file(GLOB_RECURSE fdf_HDRS ${fdf_HDRS} ${fdf_INC_DIR}/fdf/*.h)
file(GLOB_RECURSE fdf_SRCS ${fdf_SRCS} ${fdf_SRC_DIR}/*.c)

add_executable(fdf ${fdf_HDR} ${fdf_HDRS} ${fdf_SRCS})
set_property(TARGET fdf PROPERTY C_STANDARD 90)
target_include_directories(fdf PUBLIC ${fdf_INC_DIR})
target_link_libraries(fdf PUBLIC ft)
add_definitions(-Wno-error=unused-command-line-argument)

target_compile_definitions(fdf
    PRIVATE $<$<CONFIG:Debug>:DEBUG>$<$<CONFIG:Release>:NDEBUG>)
if (MSVC)
    target_compile_options(fdf
        PRIVATE /MT$<$<CONFIG:Debug>:d> /Oy /W3
        PRIVATE /D_CRT_SECURE_NO_WARNINGS /Dinline=__inline
        PRIVATE /O$<$<CONFIG:Debug>:d>$<$<CONFIG:Release>:x>)
else ()
    target_compile_options(fdf
        PRIVATE -Wall -Werror -Wextra -fomit-frame-pointer -ansi
        PRIVATE -Wno-missing-field-initializers -Wno-missing-braces
        PRIVATE -O$<$<CONFIG:Debug>:0 -g3>$<$<CONFIG:Release>:3>)
endif ()
