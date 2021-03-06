cmake_minimum_required(VERSION 2.8.8)
project(libe57_metadata)

set (libe57_metadata_VERSION_MAJOR 0)
set (libe57_metadata_VERSION_MINOR 1)

include_directories("${PROJECT_SOURCE_DIR}")
include_directories("${PROJECT_BINARY_DIR}")
include_directories("${PROJECT_SOURCE_DIR}/include")
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)

if(CMAKE_COMPILER_IS_GNUCXX)
	add_definitions(-fPIC)
	add_definitions(-O3)
	add_definitions(-g)
	add_definitions(-std=c++1y)
	add_definitions(-fPIC)
endif()

find_package(Eigen)
if(CMAKE_COMPILER_IS_GNUCXX)
    set(Boost_USE_STATIC_LIBS OFF)
else()
    set(Boost_USE_STATIC_LIBS ON)
endif()
#set(Boost_USE_STATIC_RUNTIME ON)
find_package(Boost COMPONENTS system filesystem program_options)
find_package(Cereal)
find_package(E57Ref)
if(CMAKE_COMPILER_IS_GNUCXX)
    set(Xerces_USE_STATIC_LIBS Off)
    find_package(E57Simple)
else()
    set(Xerces_USE_STATIC_LIBS On)
endif()
find_package(Xerces)
if (Xerces_USE_STATIC_LIBS)
add_definitions(-DXERCES_STATIC_LIBRARY)
endif()

file(TO_NATIVE_PATH "${CMAKE_SOURCE_DIR}" WIN_SOURCE_DIR)
configure_file(e57_metadata_wrapper/e57_metadata_wrapper.csproj "${CMAKE_BINARY_DIR}/e57_metadata_wrapper.csproj")
include_external_msproject(
	e57_metadata_wrapper
	${CMAKE_BINARY_DIR}/e57_metadata_wrapper.csproj
	TYPE FAE04EC0-301F-11D3-BF4B-00C04F79EFBC
)

file (GLOB_RECURSE cpplibh RELATIVE "${PROJECT_SOURCE_DIR}" "e57_metadata/*.hpp")
file (GLOB_RECURSE cpplib RELATIVE "${PROJECT_SOURCE_DIR}" "e57_metadata/*.cpp")
file (GLOB_RECURSE testcpp RELATIVE "${PROJECT_SOURCE_DIR}" "e57_metadata_extractor/*.cpp")
#file (GLOB_RECURSE units RELATIVE "${PROJECT_SOURCE_DIR}" "test/units/*.cpp")
if (Boost_FOUND AND EIGEN_FOUND AND CEREAL_FOUND AND E57REF_FOUND AND Xerces_FOUND AND (E57SIMPLE_FOUND OR NOT CMAKE_COMPILER_IS_GNUCXX))
	include_directories(${EIGEN_INCLUDE_DIRS})
	include_directories(${CEREAL_INCLUDE_DIRS})
	include_directories(${Boost_INCLUDE_DIRS})
	include_directories(${E57REF_INCLUDE_DIRS})

	link_directories(${E57REF_LIBRARY_DIRS})
	link_directories(${Boost_LIBRARY_DIRS})

    if(CMAKE_COMPILER_IS_GNUCXX)
        include_directories(${E57SIMPLE_INCLUDE_DIRS})
        link_directories(${E57SIMPLE_LIBRARY_DIRS})
    endif()

	add_library(e57_metadata SHARED ${cpplib} ${cpplibh})
	if(CMAKE_COMPILER_IS_GNUCXX)
		target_link_libraries(e57_metadata ${Boost_LIBRARIES} ${E57REF_LIBRARIES} ${E57SIMPLE_LIBRARIES} ${Xerces_LIBRARY} "dl")
	else()
		target_link_libraries(e57_metadata ${Boost_LIBRARIES} ${E57REF_LIBRARIES} ${Xerces_LIBRARY})
	endif()
	add_executable(e57_metadata_extractor ${testcpp})
	target_link_libraries(e57_metadata_extractor e57_metadata)

	# install binary
    if (WIN32)
        install (TARGETS e57_metadata DESTINATION bin)
    else()
        install (TARGETS e57_metadata DESTINATION lib)
    endif(WIN32)

    install (TARGETS e57_metadata_extractor DESTINATION bin)

    if (WIN32)
        install (FILES "${CMAKE_BINARY_DIR}/bin/Release/e57_metadata_wrapper.exe" DESTINATION bin)
    endif(WIN32)
	# install header
    if (WIN32)
        install (FILES ${cpplibh} DESTINATION include)
        install (FILES "e57_metadata_wrapper/e57_metadata_wrapper.cs" DESTINATION include)
    else()
        install (FILES ${cpplibh} DESTINATION include/e57_metadata)
    endif(WIN32)
endif()

