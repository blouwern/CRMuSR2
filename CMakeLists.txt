cmake_minimum_required(VERSION 3.21)
# export compile commands for language server to trace tags
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Enable MSVC_RUNTIME_LIBRARY target property
# See https://cmake.org/cmake/help/latest/policy/CMP0091.html
cmake_policy(SET CMP0091 NEW)
# Set CMP0077 to new in order to configure options for build-in libraries
# See https://discourse.cmake.org/t/what-is-the-correct-way-to-set-options-of-a-project-before-fetch-content/268/6
# See also https://cmake.org/cmake/help/latest/policy/CMP0077.html
cmake_policy(SET CMP0077 NEW)
if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.24)
    # ExternalProject_Add sets the timestamps of extracted contents to the time of extraction
    # See https://cmake.org/cmake/help/latest/policy/CMP0135.html
    cmake_policy(SET CMP0135 NEW)
endif()

project(CRMuSR2 VERSION 0.0.0
    LANGUAGES C CXX)

# =============================================================================
# Variables
# =============================================================================

# Dirs
set(CRMUSR2_PROJECT_ROOT_DIR ${PROJECT_SOURCE_DIR})
set(CRMUSR2_PROJECT_CMAKE_DIR ${CRMUSR2_PROJECT_ROOT_DIR}/cmake)
set(PROJECT_SOURCE_DIR ${CRMUSR2_PROJECT_ROOT_DIR}/src)
set(CRMUSR2_PROJECT_3RDPARTY_DIR ${CRMUSR2_PROJECT_ROOT_DIR}/thirdparty)

# Install dirs
include(GNUInstallDirs)
set(CRMUSR2_DATAROOTDIR ${CMAKE_INSTALL_DATAROOTDIR}/CRMuSR2)

# =============================================================================
# Options
# =============================================================================

include(CMakeDependentOption)

# Basic
# Options (ON/OFF)
option(CRMUSR2_BUILTIN_GENFIT "Use built-in GenFit (network or pre-downloaded source is required)." ON)
option(CRMUSR2_BUILTIN_GENFIT_EVENT_DISPLAY "Build GenFit event display module if GenFit is built-in." ON)
option(CRMUSR2_BUILTIN_CRMUSR2_OFFLINE_DATA "Use built-in offline data (network or pre-downloaded data are required)." OFF)
option(CRMUSR2_BUILTIN_MUSTARD "Use built-in Mustard (network or pre-downloaded source is required)." OFF)
option(CRMUSR2_BUILTIN_CADMESH "Use built-in CADMesh (network or pre-downloaded source is required)." OFF)
option(CRMUSR2_INSTALL_OFFLINE_DATA "Install offline data. If disabled, offline data need to be installed manually." ON)

# Advance
# Options (ON/OFF)
option(CRMUSR2_ENABLE_ASAN_IN_DEBUG_BUILD "Enable AddressSanitizer in debug build" OFF)
option(CRMUSR2_ENABLE_IPO "Bulid CRMuSR2 with interprocedural optimization" ON)
option(CRMUSR2_ENABLE_UBSAN_IN_DEBUG_BUILD "Enable UndefinedBehaviorSanitizer in debug build" ON)
option(CRMUSR2_FULL_UNITY_BUILD "Building CRMuSR2 use unity build technique COMPLETELY." OFF)
option(CRMUSR2_USE_SHARED_MSVC_RT "Select the MSVC runtime library for use (MSVC only). ON for shared (.dll), OFF for static (.lib). If you run into link error related to MSVC runtime, you can try flip this." ON)
option(CRMUSR2_SHOW_EVEN_MORE_COMPILER_WARNINGS "Add compiler flag to show even more compiler warnings (GCC: -Weffc++, Clang: -Weverything, MSVC: /Wall)." OFF)
cmake_dependent_option(CRMUSR2_ENABLE_UNITY_BUILD "Build CRMuSR2 with unity build technique." OFF "NOT CRMuSR2_FULL_UNITY_BUILD" ON)
cmake_dependent_option(CRMUSR2_SHOW_MORE_COMPILER_WARNINGS "Show compiler warnings raise from external dependencies." OFF "NOT CRMuSR2_SHOW_EVEN_MORE_COMPILER_WARNINGS" ON)
set(BUILD_SHARED_LIBS OFF CACHE INTERNAL "Build using shared libraries")
set(CRMUSR2_BUILTIN_CRMUSR2_OFFLINE_DATA_VERSION 0.0.1 CACHE STRING "Set built-in offline data version (if required).")
set(CRMUSR2_BUILTIN_MUSTARD_VERSION 0.25.1222 CACHE STRING "Set built-in Mustard version (if required).")
set(CRMUSR2_BUILTIN_CADMESH_VERSION 2.0.3 CACHE STRING "Set built-in CADMesh version (if required).")

# =============================================================================
# Installation path
# =============================================================================

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set_property(CACHE CMAKE_INSTALL_PREFIX PROPERTY VALUE ${CRMUSR2_PROJECT_ROOT_DIR}/install)
endif()
message(STATUS "Install path: ${CMAKE_INSTALL_PREFIX} (add -DCMAKE_INSTALL_PREFIX=<install_path> into CMake command if you wish to change it)")

# =============================================================================
# Global compile options
# =============================================================================

include(${CRMUSR2_PROJECT_CMAKE_DIR}/GlobalCompileConfig.cmake)

# =============================================================================
# Dependencies
# =============================================================================

# Required:

# Mustard
include(${CRMUSR2_PROJECT_CMAKE_DIR}/LookForMustard.cmake)

# Required, built-in if not found:

# GenFit
include(${CRMUSR2_PROJECT_CMAKE_DIR}/LookForGenFit.cmake)
# PMP
# include(${CRMUSR2_PROJECT_CMAKE_DIR}/LookForPMP.cmake)

# data
if(CRMUSR2_INSTALL_OFFLINE_DATA)
include(${CRMUSR2_PROJECT_CMAKE_DIR}/LookForCRMuSR2OfflineData.cmake)
else()
message(NOTICE "***Notice: Offline data installation disabled, offline data need to be installed manually")
endif()

# =============================================================================
# Let's go!
# =============================================================================

# Config for CRMuSR2
include(${CRMUSR2_PROJECT_CMAKE_DIR}/CRMuSR2CompileConfig.cmake)
# libraries
add_subdirectory(${PROJECT_SOURCE_DIR})
# main program
add_executable(CRMuSR2 CRMuSR2.c++)
target_link_libraries(CRMuSR2
    # AppCRMuSR2Reconstruction
    AppCRMuSR2Simulation
    # AppCRMuSR2Utility
    Mustard::Mustard)
install(TARGETS CRMuSR2 DESTINATION ${CMAKE_INSTALL_BINDIR})
