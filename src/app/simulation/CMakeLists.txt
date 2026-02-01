file(GLOB_RECURSE AppCRMuSR2Simulation_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.c++)
add_library(AppCRMuSR2Simulation STATIC ${AppCRMuSR2Simulation_SOURCES})
target_include_directories(AppCRMuSR2Simulation PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(AppCRMuSR2Simulation PUBLIC CRMuSR2Data
                                               CRMuSR2Detector
                                               CRMuSR2Simulation
                                               Mustard::Mustard) 

add_subdirectory(SimCRMu)
