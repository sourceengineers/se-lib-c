cmake_minimum_required (VERSION 3.5)

# Set the name of the library
set(SE_LIB_C se-lib-c)

# Set the version
set(SE_LIB_C_MAJOR_VERSION 0)
set(SE_LIB_C_MINOR_VERSION 1)
set(SE_LIB_C_PATCH_VERSION 0)
set(SE_LIB_C_VERSION
		${SE_LIB_C_MAJOR_VERSION}.${SE_LIB_C_MINOR_VERSION}.${SE_LIB_C_PATCH_VERSION})

project (${SE_LIB_C})

set(SE_LIB_C_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

include(GNUInstallDirs)

set(SE_LIB_SOURCES_IN cmake/SeLibCSources.cmake.in)
set(SE_LIB_CONFIG_IN cmake/SeLibCConfig.cmake.in)
set(SE_LIB_CONFIG_VERSION_IN cmake/SeLibCConfigVersion.cmake.in)

#Add the library sources
include(${SE_LIB_SOURCES_IN})

add_library(${SE_LIB_C} STATIC ${SE_LIB_C_SOURCES})

target_include_directories(
		${SE_LIB_C}
		PUBLIC
		$<INSTALL_INTERFACE:include>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

if(SE_LIB_C_BUILD_TESTS)
	enable_testing()
	set(SE_LIB_C_TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test)
	add_subdirectory(test)
endif()

# Installing the lib and headers
install(TARGETS ${SE_LIB_C} EXPORT ${SE_LIB_C} ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}" COMPONENT library)
install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include" DESTINATION "${CMAKE_INSTALL_PREFIX}")

# Installing the lib and headers

# Add all targets to the build-tree export set
export(TARGETS ${SE_LIB_C} NAMESPACE SeLibC:: FILE "${PROJECT_BINARY_DIR}/SeLibCTargets.cmake")
export(PACKAGE ${SE_LIB_C})

set(CONF_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}" "${PROJECT_BINARY_DIR}")
configure_file(${SE_LIB_CONFIG_IN} "${PROJECT_BINARY_DIR}/SeLibCConfig.cmake" @ONLY)
set(CONF_INCLUDE_DIRS "\${SE_LIB_C_CMAKE_DIR}/${REL_INCLUDE_DIR}")
configure_file(${SE_LIB_CONFIG_IN} "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/SeLibCConfig.cmake" @ONLY)
configure_file(${SE_LIB_CONFIG_VERSION_IN} "${PROJECT_BINARY_DIR}/SeLibCConfigVersion.cmake" @ONLY)

# Install the MyLibConfig.cmake and MyLibConfigVersion.cmake
install(FILES
		"${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/SeLibCConfig.cmake"
		"${PROJECT_BINARY_DIR}/SeLibCConfigVersion.cmake"
		DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/SeLibC COMPONENT dev)

# Install the export set for use with the install-tree
install(EXPORT ${SE_LIB_C} DESTINATION "${CMAKE_INSTALL_LIBDIR}" COMPONENT dev)