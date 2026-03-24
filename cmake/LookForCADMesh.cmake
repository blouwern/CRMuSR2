message(STATUS "Looking for CADMesh")

set(CRMUSR2_CADMESH_MINIMUM_REQUIRED 2.0.3)

if(NOT CRMuSR2_BUILTIN_CADMESH)
    find_package(CADMesh ${CRMUSR2_CADMESH_MINIMUM_REQUIRED})
    if(NOT CADMesh_FOUND)
        set(CRMuSR2_BUILTIN_CADMESH ON)
        message(NOTICE "***Notice: CADMesh not found (minimum required is ${CRMUSR2_CADMESH_MINIMUM_REQUIRED}). For the time turning on CRMuSR2_BUILTIN_CADMESH")
    endif()
endif()

if(CRMuSR2_BUILTIN_CADMESH)
    message(STATUS "CRMuSR2 will use built-in CADMesh")
    # check built-in version
    if(CRMUSR2_BUILTIN_CADMESH_VERSION VERSION_LESS CRMUSR2_CADMESH_MINIMUM_REQUIRED)
        message(NOTICE "***Notice: Provided CRMUSR2_BUILTIN_CADMESH_VERSION is ${CRMUSR2_BUILTIN_CADMESH_VERSION}, which is less than the requirement (${CRMUSR2_CADMESH_MINIMUM_REQUIRED}). Changing to ${CRMUSR2_CADMESH_MINIMUM_REQUIRED}")
        set(CRMUSR2_BUILTIN_CADMESH_VERSION ${CRMUSR2_CADMESH_MINIMUM_REQUIRED})
    endif()
    # set download dest and URL
    set(CRMUSR2_BUILTIN_CADMESH_SRC_DIR "${CRMuSR2_PROJECT_3RDPARTY_DIR}/CADMesh-${CRMUSR2_BUILTIN_CADMESH_VERSION}")
    set(CRMUSR2_BUILTIN_CADMESH_URL "https://github.com/christopherpoole/CADMesh/archive/refs/tags/v${CRMUSR2_BUILTIN_CADMESH_VERSION}.tar.gz")
    # reuse or download
    include(FetchContent)
    if(EXISTS "${CRMUSR2_BUILTIN_CADMESH_SRC_DIR}/CMakeLists.txt")
        FetchContent_Declare(CADMesh SOURCE_DIR "${CRMUSR2_BUILTIN_CADMESH_SRC_DIR}")
        message(STATUS "Reusing CADMesh source ${CRMUSR2_BUILTIN_CADMESH_SRC_DIR}")
    else()
        FetchContent_Declare(CADMesh SOURCE_DIR "${CRMUSR2_BUILTIN_CADMESH_SRC_DIR}"
                                    URL "${CRMUSR2_BUILTIN_CADMESH_URL}")
        message(STATUS "CADMesh will be downloaded from ${CRMUSR2_BUILTIN_CADMESH_URL} to ${CRMUSR2_BUILTIN_CADMESH_SRC_DIR}")
    endif()
    # set options
    # uses CACHE INTERNAL variables to propagate options. see https://discourse.cmake.org/t/what-is-the-correct-way-to-set-options-of-a-project-before-fetch-content/268/4
    # configure it
    message(STATUS "Downloading (if required) and configuring CADMesh (version: ${CRMUSR2_BUILTIN_CADMESH_VERSION})")
    FetchContent_MakeAvailable(CADMesh)
    message(STATUS "Downloading (if required) and configuring CADMesh (version: ${CRMUSR2_BUILTIN_CADMESH_VERSION}) - done")
    # check download
    if(NOT EXISTS "${CRMUSR2_BUILTIN_CADMESH_SRC_DIR}/CMakeLists.txt")
        file(REMOVE_RECURSE "${CMAKE_BINARY_DIR}/_deps/cadmesh-build")
        file(REMOVE_RECURSE "${CMAKE_BINARY_DIR}/_deps/cadmesh-subbuild")
        message(FATAL_ERROR "It seems that the download of CADMesh has failed. You can try running cmake again, or manually download CADMesh from ${CRMUSR2_BUILTIN_CADMESH_URL} and extract it to ${CRMuSR2_PROJECT_3RDPARTY_DIR} (and keep the directory structure). If the error persists, you can try cleaning the build tree and restarting the build.")
    endif()
endif()

if(NOT CRMuSR2_BUILTIN_CADMESH)
    message(STATUS "Looking for CADMesh - found (version: ${CADMesh_VERSION})")
else()
    message(STATUS "Looking for CADMesh - built-in (version: ${CRMUSR2_BUILTIN_CADMESH_VERSION})")
    set(CADMESH_INCLUDE_DIRS "${CRMUSR2_BUILTIN_CADMESH_SRC_DIR}")
endif()
