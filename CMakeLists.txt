cmake_minimum_required (VERSION 3.5)

################################################################################
# Library name
################################################################################
set(SE_LIB_C se-lib-c)
project (${SE_LIB_C})

################################################################################
# Version
################################################################################
set(SE_LIB_C_MAJOR_VERSION 0)
set(SE_LIB_C_MINOR_VERSION 1)
set(SE_LIB_C_PATCH_VERSION 0)
set(SE_LIB_C_VERSION
		${SE_LIB_C_MAJOR_VERSION}.${SE_LIB_C_MINOR_VERSION}.${SE_LIB_C_PATCH_VERSION})

################################################################################
# Sources and files
################################################################################
set(SE_LIB_C_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(SE_LIB_SOURCES_IN cmake/SeLibCSources.cmake)
set(SE_LIB_CONFIG_IN cmake/SeLibCConfig.cmake.in)
set(SE_LIB_CONFIG_VERSION_IN cmake/SeLibCConfigVersion.cmake.in)
#Add the library sources
include(${SE_LIB_SOURCES_IN})
#Add GNU paths
include(GNUInstallDirs)

################################################################################
# Generate the library
################################################################################
add_library(${SE_LIB_C} STATIC ${SE_LIB_C_SOURCES})

# Add the headers
target_include_directories(
		${SE_LIB_C}
		PUBLIC
		$<INSTALL_INTERFACE:include>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

################################################################################
# Add testing if enabled
################################################################################
enable_testing()
set(SE_LIB_C_TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test)
add_subdirectory(test EXCLUDE_FROM_ALL)

################################################################################
# Export the target
################################################################################
export(TARGETS ${SE_LIB_C} NAMESPACE SeLibC:: FILE "${PROJECT_BINARY_DIR}/SeLibCTargets.cmake")
export(PACKAGE ${SE_LIB_C})

################################################################################
# Install the library and headers
################################################################################
install(TARGETS ${SE_LIB_C} EXPORT SeLibCTargets ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}" COMPONENT library)
install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include" DESTINATION "${CMAKE_INSTALL_PREFIX}")

################################################################################
# Generate the configuration
################################################################################
set(CONF_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}" "${PROJECT_BINARY_DIR}")
configure_file(${SE_LIB_CONFIG_IN} "${PROJECT_BINARY_DIR}/SeLibCConfig.cmake" @ONLY)
set(CONF_INCLUDE_DIRS "\${SE_LIB_C_CMAKE_DIR}/${REL_INCLUDE_DIR}")
configure_file(${SE_LIB_CONFIG_IN} "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/SeLibCConfig.cmake" @ONLY)
configure_file(${SE_LIB_CONFIG_VERSION_IN} "${PROJECT_BINARY_DIR}/SeLibCConfigVersion.cmake" @ONLY)

add_definitions(-DUNIT_TEST)

################################################################################
# Install the generated files
################################################################################
install(FILES
		"${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/SeLibCConfig.cmake"
		"${PROJECT_BINARY_DIR}/SeLibCConfigVersion.cmake"
		DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/SeLibC COMPONENT dev)
install(EXPORT SeLibCTargets DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/SeLibC" COMPONENT dev)