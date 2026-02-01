message(STATUS "Looking for Mustard")

set(CRMUSR2_MUSTARD_MINIMUM_REQUIRED 0.25.1222)

if(NOT CRMUSR2_BUILTIN_MUSTARD)
    find_package(Mustard ${CRMUSR2_MUSTARD_MINIMUM_REQUIRED})
    if(NOT Mustard_FOUND)
        set(CRMUSR2_BUILTIN_MUSTARD ON)
        message(NOTICE "***Notice: Mustard not found (minimum required is ${CRMUSR2_MUSTARD_MINIMUM_REQUIRED}). For the time turning on CRMUSR2_BUILTIN_MUSTARD")
    endif()
endif()

if(CRMUSR2_BUILTIN_MUSTARD)
    message(STATUS "CRMUSR2 will use built-in Mustard")
    # check built-in version
    if(CRMUSR2_BUILTIN_MUSTARD_VERSION VERSION_LESS CRMUSR2_MUSTARD_MINIMUM_REQUIRED)
        message(NOTICE "***Notice: Provided CRMUSR2_BUILTIN_MUSTARD_VERSION is ${CRMUSR2_BUILTIN_MUSTARD_VERSION}, which is less than the requirement (${CRMUSR2_MUSTARD_MINIMUM_REQUIRED}). Changing to ${CRMUSR2_MUSTARD_MINIMUM_REQUIRED}")
        set(CRMUSR2_BUILTIN_MUSTARD_VERSION ${CRMUSR2_MUSTARD_MINIMUM_REQUIRED})
    endif()
    # set download dest and URL
    set(CRMUSR2_BUILTIN_MUSTARD_SRC_DIR "${CRMUSR2_PROJECT_3RDPARTY_DIR}/Mustard-${CRMUSR2_BUILTIN_MUSTARD_VERSION}")
    set(CRMUSR2_BUILTIN_MUSTARD_URL "https://github.com/zhao-shihan/Mustard/archive/refs/tags/v${CRMUSR2_BUILTIN_MUSTARD_VERSION}.tar.gz")
    # reuse or download
    include(FetchContent)
    if(EXISTS "${CRMUSR2_BUILTIN_MUSTARD_SRC_DIR}/CMakeLists.txt")
        FetchContent_Declare(Mustard SOURCE_DIR "${CRMUSR2_BUILTIN_MUSTARD_SRC_DIR}")
        message(STATUS "Reusing Mustard source ${CRMUSR2_BUILTIN_MUSTARD_SRC_DIR}")
    else()
        FetchContent_Declare(Mustard SOURCE_DIR "${CRMUSR2_BUILTIN_MUSTARD_SRC_DIR}"
                                     URL "${CRMUSR2_BUILTIN_MUSTARD_URL}")
        message(STATUS "Mustard will be downloaded from ${CRMUSR2_BUILTIN_MUSTARD_URL} to ${CRMUSR2_BUILTIN_MUSTARD_SRC_DIR}")
    endif()
    # set options
    set(MUSTARD_ENABLE_ASAN_IN_DEBUG_BUILD ${CRMUSR2_ENABLE_ASAN_IN_DEBUG_BUILD} CACHE INTERNAL "")
    set(MUSTARD_ENABLE_IPO ${CRMUSR2_ENABLE_IPO} CACHE INTERNAL "")
    set(MUSTARD_ENABLE_UBSAN_IN_DEBUG_BUILD ${CRMUSR2_ENABLE_UBSAN_IN_DEBUG_BUILD} CACHE INTERNAL "")
    set(MUSTARD_FULL_UNITY_BUILD ${CRMUSR2_FULL_UNITY_BUILD} CACHE INTERNAL "")
    set(MUSTARD_SHOW_EVEN_MORE_COMPILER_WARNINGS ${CRMUSR2_SHOW_EVEN_MORE_COMPILER_WARNINGS} CACHE INTERNAL "")
    set(MUSTARD_SHOW_MORE_COMPILER_WARNINGS ${CRMUSR2_SHOW_MORE_COMPILER_WARNINGS} CACHE INTERNAL "")
    set(MUSTARD_USE_SHARED_MSVC_RT ${CRMUSR2_USE_SHARED_MSVC_RT} CACHE INTERNAL "")
    # configure it
    message(STATUS "Downloading (if required) and configuring Mustard (version: ${CRMUSR2_BUILTIN_MUSTARD_VERSION})")
    FetchContent_MakeAvailable(Mustard)
    message(STATUS "Downloading (if required) and configuring Mustard (version: ${CRMUSR2_BUILTIN_MUSTARD_VERSION}) - done")
    # check download
    if(NOT EXISTS "${CRMUSR2_BUILTIN_MUSTARD_SRC_DIR}/CMakeLists.txt")
        file(REMOVE_RECURSE "${CMAKE_BINARY_DIR}/_deps/mustard-build")
        file(REMOVE_RECURSE "${CMAKE_BINARY_DIR}/_deps/mustard-subbuild")
        message(FATAL_ERROR "It seems that the download of Mustard has failed. You can try running cmake again, or manually download Mustard from ${CRMUSR2_BUILTIN_MUSTARD_URL} and extract it to ${CRMUSR2_PROJECT_3RDPARTY_DIR} (and keep the directory structure). If the error persists, you can try cleaning the build tree and restarting the build.")
    endif()
endif()

if(NOT CRMUSR2_BUILTIN_MUSTARD)
    message(STATUS "Looking for Mustard - found (version: ${Mustard_VERSION})")
else()
    message(STATUS "Looking for Mustard - built-in (version: ${CRMUSR2_BUILTIN_MUSTARD_VERSION})")
endif()
