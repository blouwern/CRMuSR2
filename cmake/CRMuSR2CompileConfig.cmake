# This file is included after "find_package"s and "LookFor"s.

# =============================================================================
# CRMuSR2 at C++20
# =============================================================================

set(CMAKE_CXX_STANDARD 20 CACHE STRING "C++ standard.")
if(CMAKE_CXX_STANDARD LESS 20)
    message(FATAL_ERROR "CRMuSR2 should be built, at least, with C++20")
endif()
set(CMAKE_CXX_STANDARD_REQUIRED ON)
message(STATUS "CRMuSR2 will be compiled with C++${CMAKE_CXX_STANDARD}")

# =============================================================================
# By default, no C++ extensions available for CRMuSR2
# =============================================================================

set(CMAKE_CXX_EXTENSIONS OFF CACHE INTERNAL "Boolean specifying whether compiler specific extensions are requested.")

# =============================================================================
# Unity build for CRMuSR2
# =============================================================================

if(CRMUSR2_ENABLE_UNITY_BUILD)
    set(CMAKE_UNITY_BUILD ON)
    if(CRMUSR2_FULL_UNITY_BUILD)
        set(CMAKE_UNITY_BUILD_BATCH_SIZE 0)
    else()
        set(CMAKE_UNITY_BUILD_BATCH_SIZE 8)
    endif()
    if(CMAKE_UNITY_BUILD_BATCH_SIZE GREATER 0)
        message(STATUS "Unity build enabled for CRMuSR2 (batch size: ${CMAKE_UNITY_BUILD_BATCH_SIZE})")
    else()
        message(STATUS "Unity build enabled for CRMuSR2 (batch size: unlimited)")
    endif()
endif()

# =============================================================================
# LTO/IPO for CRMuSR2
# =============================================================================

if(CRMUSR2_ENABLE_IPO)
    include(CheckIPOSupported)
    check_ipo_supported(RESULT CRMUSR2_ENABLE_IPO_SUPPORTED
                        OUTPUT CRMUSR2_IPO_SUPPORTED_ERROR)
    if(CRMUSR2_ENABLE_IPO_SUPPORTED)
        set(CMAKE_INTERPROCEDURAL_OPTIMIZATION_RELEASE ON)
        message(STATUS "LTO/IPO enabled for CRMuSR2")
    else()
        set(CMAKE_INTERPROCEDURAL_OPTIMIZATION_RELEASE OFF)
        message(NOTICE "***Notice: LTO/IPO not supported. Turning off CMAKE_INTERPROCEDURAL_OPTIMIZATION_RELEASE")
    endif()
endif()

# =============================================================================
# Compile options and definitions for CRMuSR2
# =============================================================================

set(CRMUSR2_COMPILE_OPTIONS "")
set(CRMUSR2_COMPILE_DEFINITIONS "")

# =============================================================================
# Compile warnings for CRMuSR2
# =============================================================================

# Surpress some, if required
if(NOT CRMUSR2_SHOW_MORE_COMPILER_WARNINGS)
    if(CMAKE_COMPILER_IS_GNUCXX)
        # nothing for now
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        # nothing for now
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        # TODO: below is ancient; need update.
        # # ROOT (conditional expression is constant)
        # list(APPEND CRMUSR2_COMPILE_OPTIONS /wd4127)
        # # Common ('argument': conversion from 'type1' to 'type2', possible loss of data)
        # list(APPEND CRMUSR2_COMPILE_OPTIONS /wd4244)
        # # Common ('var': conversion from 'size_t' to 'type', possible loss of data)
        # list(APPEND CRMUSR2_COMPILE_OPTIONS /wd4267)
        # # MSVC std::tuple ('derived class' : destructor was implicitly defined as deleted because a base class destructor is inaccessible or deleted)
        # list(APPEND CRMUSR2_COMPILE_OPTIONS /wd4624)
        # # Common (The file contains a character that cannot be represented in the current code page (number). Save the file in Unicode format to prevent data loss)
        # list(APPEND CRMUSR2_COMPILE_OPTIONS /wd4819)
        # # ROOT (using a function, class member, variable, or typedef that's marked deprecated)
        # list(APPEND CRMUSR2_COMPILE_OPTIONS /wd4996)
        # # Eigen (operator 'operator-name': deprecated between enumerations of different types)
        # list(APPEND CRMUSR2_COMPILE_OPTIONS /wd5054)
    endif()
# Even more warnings, if required
elseif(CRMUSR2_SHOW_EVEN_MORE_COMPILER_WARNINGS)
    if(CMAKE_COMPILER_IS_GNUCXX)
        list(APPEND CRMUSR2_COMPILE_OPTIONS -Weffc++)
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        list(APPEND CRMUSR2_COMPILE_OPTIONS -Weverything)
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        list(APPEND CRMUSR2_COMPILE_OPTIONS /Wall)
    endif()
endif()

# =============================================================================
# Add compile options and definitions here
# =============================================================================

add_compile_options(${CRMUSR2_COMPILE_OPTIONS})
add_compile_definitions(${CRMUSR2_COMPILE_DEFINITIONS})
