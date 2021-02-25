cmake_minimum_required( VERSION 3.16 )

project( photo_info_provider )

set( CMAKE_CXX_STANDARD 17 )

#set( CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "C:/Program\ Files/Boost/boost_1_75_0" )
#set( CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "C:/Program\ Files/Boost/boost_1_75_0/libs" )
#set( Boost_COMPILER ${Boost_COMPILER} "-vc141" )

##set( VCPKG_TARGET_TRIPLET "x64-windows" )
##set( CURL_DIR "C:/vcpkg/installed/x64-windows/share/curl/" )
##set( CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "C:/vcpkg/installed/x64-windows/share/curl/")
##set( ZLIB_ROOT "C:/vcpkg/installed/x64-windows/" )
#set( OPENSSL_ROOT_DIR "C:/vcpkg/installed/x64-windows" )
#set( Boost_INCLUDE_DIR "C:/Program\ Files/Boost/boost_1_75_0" )
#set( Boost_INCLUDE_DIR "C:/vcpkg/installed/x64-windows/include" )

##set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "C:/vcpkg/installed/x64-windows/share/curl/")


include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

##include( CURLConfig )

##find_package(CURL CONFIG REQUIRED)

add_executable( photo_info_provider src/fromsomeapi_info_provider.cpp )

##target_link_libraries(photo_info_provider PRIVATE CURL::libcurl)
target_link_libraries(photo_info_provider CONAN_PKG::libcurl)
