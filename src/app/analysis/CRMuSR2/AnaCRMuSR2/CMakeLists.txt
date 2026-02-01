file(GLOB_RECURSE CRMuSR2_AnaCRMuSR2_srcs ${CMAKE_CURRENT_SOURCE_DIR}/*.c++)

add_executable(AnaCRMuSR2 ${CRMuSR2_AnaCRMuSR2_srcs})
target_link_libraries(AnaCRMuSR2 CRMuSR2Data CRMuSR2Detector Mustard::Mustard CRMuSR2Analysis)

install(TARGETS AnaCRMuSR2 DESTINATION ${CMAKE_INSTALL_BINDIR})
