cmake_minimum_required(VERSION 2.8)
project(OpenSpin)

# Define resources
set(RESOURCES res/*)

# Define sources
file(GLOB_RECURSE source_files src/*)

set(BIN_DIR ${PROJECT_SOURCE_DIR}/bin)

# Bump up warning levels appropriately for clang, gcc & msvc and build in debug mode
if(${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU" OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")

	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra -pedantic -std=c++11")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_DEBUG} -g")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELEASE} -O2")

elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")

	if (CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
		string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
	else()
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
	endif()

endif()

include_directories(include)
add_library(common src/common.c)

#Check if a toolchain is gonna be used
if(DEFINED CMAKE_TOOLCHAIN_FILE)

	set(CMAKE_TOOLCHAIN_FILE ${CMAKE_TOOLCHAIN_FILE} CACHE STRING "Toolchain file used")

	message(STATUS "Toolchain used : " ${CMAKE_TOOLCHAIN_FILE})

	# Check if the toolchain used is to build iOS application
	if(${CMAKE_TOOLCHAIN_FILE} MATCHES "iOS.cmake")

		set_source_files_properties(${RESOURCES} PROPERTIES MACOSX_PACKAGE_LOCATION Resources)
		set(CMAKE_OSX_SYSROOT iphonesimulator8.3)
		set(CMAKE_OSX_ARCHITECTURES "$(ARCHS_STANDARD_32_BIT)")
		set(MACOSX_BUNDLE_GUI_IDENTIFIER "com.github.jbltx.\${PRODUCT_NAME:identifier}")
		set(IOS_FRAMEWORKS Foundation AudioToolbox CoreGraphics QuartzCore UIKit OpenGLES)
		foreach(FW ${IOS_FRAMEWORKS})
			set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -framework ${FW}")
		endforeach()
		include_directories(/Library/Frameworks/SDL2.framework/Headers)
		link_directories(/Library/Frameworks/SDL2.framework ${CMAKE_CURRENT_SOURCE_DIR}/libs)
		add_executable(${PROJECT_NAME} MACOSX_BUNDLE ${source_files} res/Default.png res/Icon.png)
		target_link_libraries(${PROJECT_NAME} SDL2 common)

	endif()

	# Check if the toolchain used is to build Android application
	if(${CMAKE_TOOLCHAIN_FILE} STREQUAL "../toolchain/android.cmake")

	endif()

else()

	message(STATUS "No toolchain used")
	# Use FindSDL2 modules to find easily SDL2 libraries between different OS
	set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")
	find_package(SDL2 REQUIRED)
	include_directories(${SDL2_INCLUDE_DIR})
	add_executable(${PROJECT_NAME} ${source_files})
	target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY} common)
	install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${BIN_DIR})

endif()

