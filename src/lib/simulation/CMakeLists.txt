file(GLOB_RECURSE CRMUSR2_SIMULATION_SRC ${CMAKE_CURRENT_SOURCE_DIR}/CRMuSR2/*.c++)

add_library(CRMuSR2Simulation STATIC ${CRMUSR2_SIMULATION_SRC})
target_include_directories(CRMuSR2Simulation PUBLIC ${PROJECT_SOURCE_DIR}/lib/simulation)
target_link_libraries(CRMuSR2Simulation PUBLIC Mustard::Mustard CRMuSR2Data CRMuSR2Detector)
