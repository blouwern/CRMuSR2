file(GLOB_RECURSE CRMUSR2_DATA_MODEL_SRC ${CMAKE_CURRENT_SOURCE_DIR}/CRMuSR2/*.c++)

add_library(CRMuSR2Data STATIC ${CRMuSR2_DATA_MODEL_SRC})
target_include_directories(CRMuSR2Data PUBLIC ${PROJECT_SOURCE_DIR}/lib/data)
target_link_libraries(CRMuSR2Data PUBLIC Mustard::Mustard)
