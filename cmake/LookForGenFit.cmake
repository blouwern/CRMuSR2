message(STATUS "Looking for GenFit")

set(CRMUSR2_GENFIT_MINIMUM_REQUIRED 2.2.0)

if(NOT CRMUSR2_BUILTIN_GENFIT)
    find_package(genfit ${CRMUSR2_GENFIT_MINIMUM_REQUIRED})
    if(NOT genfit_FOUND)
        set(CRMUSR2_BUILTIN_GENFIT ON)
        message(NOTICE "***Notice: GenFit not found (minimum required is ${CRMUSR2_GENFIT_MINIMUM_REQUIRED}). For the time turning on CRMUSR2_BUILTIN_GENFIT")
    endif()
endif()

if(CRMUSR2_BUILTIN_GENFIT)
    message(STATUS "CRMUSR2 will use built-in GenFit")
    # set download dest and URL
    set(CRMUSR2_BUILTIN_GENFIT_SRC_DIR "${CRMUSR2_PROJECT_3RDPARTY_DIR}/GenFit-02-00-01")
    set(CRMUSR2_BUILTIN_GENFIT_URL "https://github.com/zhao-shihan/GenFit/archive/refs/heads/master.zip")
    # reuse or download
    include(FetchContent)
    if(EXISTS "${CRMUSR2_BUILTIN_GENFIT_SRC_DIR}/CMakeLists.txt")
        FetchContent_Declare(genfit SOURCE_DIR "${CRMUSR2_BUILTIN_GENFIT_SRC_DIR}")
        message(STATUS "Reusing GenFit source ${CRMUSR2_BUILTIN_GENFIT_SRC_DIR}")
    else()
        FetchContent_Declare(genfit SOURCE_DIR "${CRMUSR2_BUILTIN_GENFIT_SRC_DIR}"
                                    URL "${CRMUSR2_BUILTIN_GENFIT_URL}")
        message(STATUS "GenFit will be downloaded from ${CRMUSR2_BUILTIN_GENFIT_URL} to ${CRMUSR2_BUILTIN_GENFIT_SRC_DIR}")
    endif()
    # set options
    set(GF_BUILD_EVENT_DISPLAY ${CRMUSR2_BUILTIN_GENFIT_EVENT_DISPLAY} CACHE INTERNAL "")
    # configure it
    message(STATUS "Downloading (if required) and configuring GenFit (version: 2.2.0)")
    FetchContent_MakeAvailable(genfit)
    message(STATUS "Downloading (if required) and configuring GenFit (version: 2.2.0) - done")
    # check download
    if(NOT EXISTS "${CRMUSR2_BUILTIN_GENFIT_SRC_DIR}/CMakeLists.txt")
        file(REMOVE_RECURSE "${CMAKE_BINARY_DIR}/_deps/genfit-build")
        file(REMOVE_RECURSE "${CMAKE_BINARY_DIR}/_deps/genfit-subbuild")
        message(FATAL_ERROR "It seems that the download of GenFit has failed. You can try running cmake again, or manually download GenFit from ${CRMUSR2_BUILTIN_GENFIT_URL} and extract it to ${CRMUSR2_PROJECT_3RDPARTY_DIR} (and keep the directory structure). If the error persists, you can try cleaning the build tree and restarting the build.")
    endif()
endif()

if(NOT CRMUSR2_BUILTIN_GENFIT)
    message(STATUS "Looking for GenFit - found (version: ${genfit_VERSION})")
    set(GENFIT_INCLUDE_DIRS "${genfit_DIR}/include")
else()
    message(STATUS "Looking for GenFit - built-in (version: 2.2.0)")
    set(GENFIT_INCLUDE_DIRS "${CRMUSR2_BUILTIN_GENFIT_SRC_DIR}/core/include"
                            "${CRMUSR2_BUILTIN_GENFIT_SRC_DIR}/eventDisplay/include"
                            "${CRMUSR2_BUILTIN_GENFIT_SRC_DIR}/fields/include"
                            "${CRMUSR2_BUILTIN_GENFIT_SRC_DIR}/finitePlanes/include"
                            "${CRMUSR2_BUILTIN_GENFIT_SRC_DIR}/fitters/include"
                            "${CRMUSR2_BUILTIN_GENFIT_SRC_DIR}/GBL/include"
                            "${CRMUSR2_BUILTIN_GENFIT_SRC_DIR}/measurements/include"
                            "${CRMUSR2_BUILTIN_GENFIT_SRC_DIR}/trackReps/include"
                            "${CRMUSR2_BUILTIN_GENFIT_SRC_DIR}/utilities/include")
endif()
