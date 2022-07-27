cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_STANDARD 11)

project(vineyard LANGUAGES C CXX VERSION ${VINEYARD_VERSION})

set(BUILDFILE main.cc CACHE STRING "Which file to build")

option(BUILD_SHARED_LIBS "Build shared libraries" ON)
option(USE_EXTERNAL_REDIS_LIBS "Build with external redis-plus-plus library rather than the submodule one" ON)
option(USE_EXTERNAL_HIREDIS_LIBS "Build with external redis-plus-plus library rather than the submodule one" ON)

macro(add_subdirectory_shared directory)
    set(BUILD_SHARED_LIBS_SAVED "${BUILD_SHARED_LIBS}")
    set(BUILD_SHARED_LIBS ON)
    add_subdirectory(${directory} ${ARGN})
    set(BUILD_SHARED_LIBS "${BUILD_SHARED_LIBS_SAVED}")
endmacro(add_subdirectory_shared)

macro(add_subdirectory_static directory)
    set(BUILD_SHARED_LIBS_SAVED "${BUILD_SHARED_LIBS}")
    set(BUILD_SHARED_LIBS OFF)
    add_subdirectory(${directory} ${ARGN})
    set(BUILD_SHARED_LIBS "${BUILD_SHARED_LIBS_SAVED}")
endmacro(add_subdirectory_static)

macro(find_hiredis)
    if(USE_EXTERNAL_HIREDIS_LIBS)
    # not use find_package, because maybe we don't have hiredis-config.cmake
        find_path(HIREDIS_HEADER_PATH hiredis)
        find_library(HIREDIS_LIBRARY hiredis)
        if(HIREDIS_HEADER_PATH AND HIREDIS_LIBRARY)
            message(STATUS "\n from shihao: Found hiredis")
            set(HIREDIS_INCLUDE_DIR ${HIREDIS_HEADER_PATH})
            set(HIREDIS_LIBRARIES ${HIREDIS_LIBRARY})
        else()
            message(WARNING "hiredis not found, will use the bundled one from git submodules.")
            include("cmake/BuildHiredis.cmake")
        endif()
    else()
        include("cmake/BuildHiredis.cmake")
    endif()
endmacro(find_hiredis)

# ToDo： 需要解决没有使用cmake安装hiredis的情况
macro(find_redis_plus_plus)
	set(REDIS_PLUS_PLUS_CXX_STANDARD 11)
    if(USE_EXTERNAL_REDIS_LIBS)
        # not use find_package, because of hiredis
        find_path(REDIS_PLUS_PLUS_HEADER sw)
        find_library(REDIS_PLUS_PLUS_LIB redis++)
        if(REDIS_PLUS_PLUS_HEADER AND REDIS_PLUS_PLUS_LIB)
            message(STATUS "\n from shihao: Found redis_plus_plus")
            set(REDIS_PLUS_PLUS_INCLUDE_DIR "${REDIS_PLUS_PLUS_HEADER}/sw")
            set(REDIS_PLUS_PLUS_LIBRARIES ${REDIS_PLUS_PLUS_LIB})
        else()
            message(WARNING "redis-plus-plus not found, will use the bundled one from git submodules.")
            include("cmake/BuildRedisCpp.cmake")
        endif()
    else()
        include("cmake/BuildRedisCpp.cmake")
    endif()
endmacro(find_redis_plus_plus)

# build main
find_hiredis()
find_redis_plus_plus()

add_executable(main ${BUILDFILE})

find_library(BOOST_THREAD_LIBRARIES boost_thread)
find_library(BOOST_SYSTEM_LIBRARIES boost_system)
find_library(UV_LIBRARIES uv)
if(BOOST_THREAD_LIBRARIES AND BOOST_SYSTEM_LIBRARIES AND UV_LIBRARIES)
	message(STATUS "\n from shihao: all found")
	message(STATUS "${BOOST_THREAD_LIBRARIES}")
	message(STATUS "${BOOST_SYSTEM_LIBRARIES}")
	message(STATUS "${UV_LIBRARIES}")
endif()
target_link_libraries(main ${HIREDIS_LIBRARIES} ${REDIS_PLUS_PLUS_LIBRARIES} ${BOOST_THREAD_LIBRARIES} ${BOOST_SYSTEM_LIBRARIES} ${UV_LIBRARIES} pthread)
#target_include_directories(main PRIVATE ${HIREDIS_INCLUDE_DIR} ${REDIS_PLUS_PLUS_INCLUDE_DIR})

target_include_directories(main PUBLIC ${HIREDIS_INCLUDE_DIR} ${REDIS_PLUS_PLUS_INCLUDE_DIR})
