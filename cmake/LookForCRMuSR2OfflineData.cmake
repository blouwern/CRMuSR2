
message(STATUS "Looking for crmusr2_offline_data")

set(CRMUSR2_CRMUSR2_OFFLINE_DATA_MINIMUM_REQUIRED 0.26.032513)

if(NOT CRMUSR2_BUILTIN_CRMUSR2_OFFLINE_DATA)
    find_package(crmusr2_offline_data ${CRMUSR2_CRMUSR2_OFFLINE_DATA_MINIMUM_REQUIRED})
    if(NOT crmusr2_offline_data_FOUND)
        set(CRMUSR2_BUILTIN_CRMUSR2_OFFLINE_DATA ON)
        message(NOTICE "***Notice: crmusr2_offline_data not found (minimum required is ${CRMUSR2_CRMUSR2_OFFLINE_DATA_MINIMUM_REQUIRED}). For the time turning on CRMUSR2_BUILTIN_CRMUSR2_OFFLINE_DATA")
    endif()
endif()

if(CRMUSR2_BUILTIN_CRMUSR2_OFFLINE_DATA)
    message(STATUS "CRMuSR2 will use built-in crmusr2_offline_data")
    # check built-in version
    if(CRMUSR2_BUILTIN_CRMUSR2_OFFLINE_DATA_VERSION VERSION_LESS CRMUSR2_CRMUSR2_OFFLINE_DATA_MINIMUM_REQUIRED)
        message(NOTICE "***Notice: Provided CRMUSR2_BUILTIN_CRMUSR2_OFFLINE_DATA_VERSION is ${CRMUSR2_BUILTIN_CRMUSR2_OFFLINE_DATA_VERSION}, which is less than the requirement (${CRMUSR2_CRMUSR2_OFFLINE_DATA_MINIMUM_REQUIRED}). Changing to ${CRMUSR2_CRMUSR2_OFFLINE_DATA_MINIMUM_REQUIRED}")
        set(CRMUSR2_BUILTIN_CRMUSR2_OFFLINE_DATA_VERSION ${CRMUSR2_CRMUSR2_OFFLINE_DATA_MINIMUM_REQUIRED})
    endif()
    # set download dest and URL
    set(CRMUSR2_BUILTIN_CRMUSR2_OFFLINE_DATA_SRC_DIR "${CRMUSR2_PROJECT_3RDPARTY_DIR}/crmusr2_offline_data-v${CRMUSR2_BUILTIN_CRMUSR2_OFFLINE_DATA_VERSION}")
    set(CRMUSR2_BUILTIN_CRMUSR2_OFFLINE_DATA_URL "https://github.com/blouwern/crmusr2_offline_data/archive/refs/tags/v${CRMUSR2_BUILTIN_CRMUSR2_OFFLINE_DATA_VERSION}.tar.gz")
    # reuse or download
    include(FetchContent)
    if(EXISTS "${CRMUSR2_BUILTIN_CRMUSR2_OFFLINE_DATA_SRC_DIR}/CMakeLists.txt")
        FetchContent_Declare(crmusr2_offline_data SOURCE_DIR "${CRMUSR2_BUILTIN_CRMUSR2_OFFLINE_DATA_SRC_DIR}")
        message(STATUS "Reusing crmusr2_offline_data source ${CRMUSR2_BUILTIN_CRMUSR2_OFFLINE_DATA_SRC_DIR}")
    else()
        FetchContent_Declare(crmusr2_offline_data SOURCE_DIR "${CRMUSR2_BUILTIN_CRMUSR2_OFFLINE_DATA_SRC_DIR}"
                                    URL "${CRMUSR2_BUILTIN_CRMUSR2_OFFLINE_DATA_URL}")
        message(STATUS "crmusr2_offline_data will be downloaded from ${CRMUSR2_BUILTIN_CRMUSR2_OFFLINE_DATA_URL} to ${CRMUSR2_BUILTIN_CRMUSR2_OFFLINE_DATA_SRC_DIR}")
    endif()
    # configure it
    message(STATUS "Downloading (if required) and configuring crmusr2_offline_data (version: ${CRMUSR2_BUILTIN_CRMUSR2_OFFLINE_DATA_VERSION})")
    FetchContent_MakeAvailable(crmusr2_offline_data)
    message(STATUS "Downloading (if required) and configuring crmusr2_offline_data (version: ${CRMUSR2_BUILTIN_CRMUSR2_OFFLINE_DATA_VERSION}) - done")
    # check download
    if(NOT EXISTS "${CRMUSR2_BUILTIN_CRMUSR2_OFFLINE_DATA_SRC_DIR}/CMakeLists.txt")
        file(REMOVE_RECURSE "${CMAKE_BINARY_DIR}/_deps/CRMUSR2_OFFLINE_DATA-build")
        file(REMOVE_RECURSE "${CMAKE_BINARY_DIR}/_deps/CRMUSR2_OFFLINE_DATA-subbuild")
        message(FATAL_ERROR "It seems that the download of crmusr2_offline_data has failed. You can try running cmake again, or manually download crmusr2_offline_data from ${CRMUSR2_BUILTIN_CRMUSR2_OFFLINE_DATA_URL} and extract it to ${CRMUSR2_PROJECT_3RDPARTY_DIR} (and keep the directory structure). If the error persists, you can try cleaning the build tree and restarting the build.")
    endif()
endif()

if(NOT CRMUSR2_BUILTIN_CRMUSR2_OFFLINE_DATA)
    message(STATUS "Looking for crmusr2_offline_data - found (version: ${crmusr2_offline_data_VERSION})")
else()
    message(STATUS "Looking for crmusr2_offline_data - built-in (version: ${CRMUSR2_BUILTIN_CRMUSR2_OFFLINE_DATA_VERSION})")
endif()
