file(GLOB_RECURSE CRMUSR2_DETECTOR_SRC ${CMAKE_CURRENT_SOURCE_DIR}/CRMuSR2/*.c++)

add_library(CRMuSR2Detector STATIC ${CRMUSR2_DETECTOR_SRC})
target_include_directories(CRMuSR2Detector PUBLIC ${PROJECT_SOURCE_DIR}/lib/detector ${CADMESH_INCLUDE_DIRS})
target_link_libraries(CRMuSR2Detector PUBLIC Mustard::Mustard)
