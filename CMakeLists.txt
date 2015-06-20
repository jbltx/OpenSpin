cmake_minimum_required(VERSION 3.1)
project(osef)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU" OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang" OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "AppleClang")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -std=c++11")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_DEBUG} -g")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELEASE} -O2")
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
	if (CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
		string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
	else()
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
	endif()
endif()

aux_source_directory(./src SRC_LIST)

find_package(SDL2 REQUIRED)

add_executable(${PROJECT_NAME} ${SRC_LIST})
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)

include_directories (
	./src 
	./third_party/tinyxml2 
	./third_party/inih/cpp 
	./third_party/rapidjson/include
	${SDL2_INCLUDE_DIR}
)

target_link_libraries (${PROJECT_NAME} ${SDL2_LIBRARIES})