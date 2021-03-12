cmake_minimum_required( VERSION 3.16 )

project( photo_info_provider )

set( CMAKE_CXX_STANDARD 17 )

include( ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake )
conan_basic_setup( TARGETS )

include_directories( ${CMAKE_SOURCE_DIR}/include )
include_directories( ${CMAKE_SOURCE_DIR}/json )

# Project

add_library( curl_sender src/curl_sender.cpp )

# One of the best ways is to use submodule for curl and leave conan for boost

######   Fix this  ######
# target_link_libraries( curl_sender CONAN_PKG::libcurl )
###### Remove this ######
if ( NOT XARCH_WINDOWS )
    set( XARCH_WINDOWS "x64-windows" )
endif()
if ( NOT PATH_TO_VCPKG )
    set( PATH_TO_VCPKG "C:/Program\ Files/vcpkg/" )
endif()
option( USE_STATIC_LIB ON )
message( ${PATH_TO_VCPKG} )
message( ${XARCH_WINDOWS} )
set( EXTENDED_PATH_TO_VCPKG ${PATH_TO_VCPKG}/installed/${XARCH_WINDOWS} )
message( ${EXTENDED_PATH_TO_VCPKG} )
set( CMAKE_TOOLCHAIN_FILE ${PATH_TO_VCPKG}/scripts/buildsystems/vcpkg.cmake )
set( VCPKG_TARGET_TRIPLET ${XARCH_WINDOWS} )
set( CURL_DIR ${EXTENDED_PATH_TO_VCPKG}/share/curl/ )
set( ZLIB_ROOT ${EXTENDED_PATH_TO_VCPKG} )
set( CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${EXTENDED_PATH_TO_VCPKG}/share/curl/ )
set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${EXTENDED_PATH_TO_VCPKG}/share/curl/ )
include( CURLConfig )
find_package( CURL CONFIG REQUIRED )
target_link_libraries( curl_sender PRIVATE CURL::libcurl )
###### ~~~~~~~~~~~ ######

add_library( model_unsplash src/model_unsplash.cpp )

target_link_libraries( model_unsplash curl_sender )

add_library( view_cli src/view_cli.cpp )

add_library( controller src/controller.cpp )

add_executable( ${CMAKE_PROJECT_NAME} src/main.cpp )
target_link_libraries( ${CMAKE_PROJECT_NAME} controller )
target_link_libraries( ${CMAKE_PROJECT_NAME} view_cli )
target_link_libraries( ${CMAKE_PROJECT_NAME} model_unsplash )

# Tests

add_executable( test_exe test/basic.cpp )
target_link_libraries( test_exe CONAN_PKG::boost )
target_link_libraries( test_exe controller )
target_link_libraries( test_exe model_unsplash )
