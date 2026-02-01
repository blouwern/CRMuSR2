file(GLOB_RECURSE CRMUSR2_ANALYSIS_SRC ${CMAKE_CURRENT_SOURCE_DIR}/CRMuSR2/*.c++)

add_library(CRMuSR2Analysis STATIC ${CRMUSR2_ANALYSIS_SRC})
target_include_directories(CRMuSR2Analysis PUBLIC ${PROJECT_SOURCE_DIR}/lib/analysis)
target_link_libraries(CRMuSR2Analysis PUBLIC CRMuSR2Data CRMuSR2Detector Mustard::Mustard)
