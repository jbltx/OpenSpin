cmake_minimum_required(VERSION 2.8)
project(OpenSpin)

# Use FindSDL2 modules to find easily SDL2 libraries between different OS
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")


set(LIB_MAJOR_VERSION "0")
set(LIB_MINOR_VERSION "1")
set(LIB_PATCH_VERSION "0")
set(LIB_VERSION_STRING "${LIB_MAJOR_VERSION}.${LIB_MINOR_VERSION}.${LIB_PATCH_VERSION}")

# Define manifest for OSX and iOS applications
set(MACOSX_BUNDLE_INFO_STRING "Open-Source Emulators Frontend")
set(MACOSX_BUNDLE_GUI_IDENTIFIER "com.github.jbltx.\${PRODUCT_NAME:identifier}")
set(MACOSX_BUNDLE_ICON_FILE "Icon.png")
set(MACOSX_BUNDLE_SHORT_VERSION_STRING "0.1")
set(MACOSX_BUNDLE_LONG_VERSION_STRING ${LIB_VERSION_STRING})
set(MACOSX_BUNDLE_COPYRIGHT "jbltx")
set(MACOSX_BUNDLE_BUNDLE_NAME ${PROJECT_NAME})
set(MACOSX_BUNDLE_BUNDLE_VERSION 0.1.0)

# Define resources
file(GLOB_RECURSE resource_files res/*)
set(RESOURCES ${resource_files})

# Define sources
file(GLOB_RECURSE source_files src/*)

set(BIN_DIR ${PROJECT_SOURCE_DIR}/build/release)

set(CMAKE_CONFIGURATION_TYPES Debug Release)

# Bump up warning levels appropriately for clang, gcc & msvc and build in debug mode
if(${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU" OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang" OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "Apple")

	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native -Wextra -pedantic -std=c++11 --coverage")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_DEBUG} -g")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELEASE} -O2")

elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
	set(APP_TYPE WIN32)
	add_definitions(-D_CRT_SECURE_NO_WARNINGS=1)
	if (CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
		string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
	else()
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
	endif()

endif()

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	set(APP_TYPE MACOSX_BUNDLE)
	set_source_files_properties(${RESOURCES} PROPERTIES MACOSX_PACKAGE_LOCATION Resources)
endif()

#Check if a toolchain is gonna be used
if(DEFINED CMAKE_TOOLCHAIN_FILE)

	set(CMAKE_TOOLCHAIN_FILE ${CMAKE_TOOLCHAIN_FILE} CACHE STRING "Toolchain file used")

	# Check if the toolchain used is to build iOS application
	if(${CMAKE_TOOLCHAIN_FILE} MATCHES "iOS.cmake")

		set(CMAKE_OSX_SYSROOT "iphoneos")
		set(CMAKE_OSX_ARCHITECTURES "${IOS_ARCH}")
		set(CMAKE_XCODE_ATTRIBUTE_TARGETED_DEVICE_FAMILY "1,2")
		set(CMAKE_XCODE_ATTRIBUTE_IPHONEOS_DEPLOYMENT_TARGET "8.0")
		set(LIBS SDL2)
		set(IOS_FRAMEWORKS Foundation AudioToolbox CoreGraphics QuartzCore UIKit OpenGLES)
		foreach(FW ${IOS_FRAMEWORKS})
			set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -framework ${FW}")
		endforeach()
		find_host_package(SDL2 REQUIRED)
		link_directories(${CMAKE_CURRENT_SOURCE_DIR}/libs)
		
	endif()

	# Check if the toolchain used is to build Android application
	if(${CMAKE_TOOLCHAIN_FILE} MATCHES "android.cmake")

	endif()

else()

	find_package(SDL2 REQUIRED)
	set(LIBS "${SDL2_LIBRARY}")

endif()

include_directories(include ${SDL2_INCLUDE_DIR})
add_executable(${PROJECT_NAME} ${APP_TYPE} ${source_files} ${resource_files})
target_link_libraries(${PROJECT_NAME} ${LIBS})

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${BIN_DIR} BUNDLE DESTINATION ${BIN_DIR})
