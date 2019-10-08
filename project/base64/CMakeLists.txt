cmake_minimum_required(VERSION 3.10)
set(BASE64_SRC "../../src/base64.cpp")
set(LIBRARY_OUTPUT_PATH ../../libs)
include_directories(../../include)
add_compile_options(-fPIC)
add_definitions(-D_GLIBCXX_USE_CXX11_ABI=0)
add_definitions(-std=c++11)
#add_definitions(-DINFO)
#link_directories(../../libs)
#link_libraries(liblog.a)
add_library(base64 SHARED ${BASE64_SRC})
#target_link_libraries(base64 "-Wl,--whole-archive" log "-Wl,--no-whole-archive")
#target_link_libraries(sdk 
# "-Wl,--whole-archive" #之后的库使用--whole-archive选项
# sdk_api
# sdk_dev 
#sdk_sys 
#"-Wl,--no-whole-archive")  #之后的库不使用--whole-archive选项
set_target_properties(base64 PROPERTIES CLEAN_DIRECT_OUTPUT 1)
##set_target_properties(log PROPERTIES VERSION 1.0 SOVERSION 1)
install(TARGETS base64 LIBRARY DESTINATION ${LIBRARY_OUTPUT_PATH})
#add_definitions(-DINFO)
link_directories(../../libs)
#link_libraries(liblog.a)
add_library(base64_static STATIC ${BASE64_SRC})
#target_link_libraries(base64_static "-Wl,--whole-archive" log "-Wl,--no-whole-archive")
set_target_properties(base64_static PROPERTIES OUTPUT_NAME base64)
set_target_properties(base64_static PROPERTIES CLEAN_DIRECT_OUTPUT 1)
install(TARGETS base64_static ARCHIVE DESTINATION ${LIBRARY_OUTPUT_PATH})
############
############

#set(MAIN_TEST_SRC "../../src/main_test.cpp")
#add_definitions(-D_GLIBCXX_USE_CXX11_ABI=0)
#add_definitions(-std=c++11)
#add_definitions(-DINFO)
#include_directories(../../include)
#link_directories(../../libs)
#link_libraries(liblog.a)
#add_executable(main_test ${MAIN_TEST_SRC})