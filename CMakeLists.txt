cmake_minimum_required( VERSION 3.16 )

project( photo_info_provider )

set( CMAKE_CXX_STANDARD 17 )

include( ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake )
conan_basic_setup( TARGETS )

add_executable( ${CMAKE_PROJECT_NAME} src/fromsomeapi_info_provider.cpp )
target_link_libraries( ${CMAKE_PROJECT_NAME} CONAN_PKG::libcurl )

add_executable( test_exe test/basic.cpp )
target_link_libraries( test_exe CONAN_PKG::boost )