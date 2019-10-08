cmake_minimum_required(VERSION 3.10)
set(RAND_SRC  "../../src/rand.cpp")
set(LIBRARY_OUTPUT_PATH ../../libs)
include_directories(../../include)
add_compile_options(-fPIC)
add_definitions(-D_GLIBCXX_USE_CXX11_ABI=0)
add_definitions(-std=c++11)
#add_definitions(-DINFO)
link_directories(../../libs)
link_libraries(libaes.a)
add_library(rand SHARED ${RAND_SRC})
#target_link_libraries(base64 "-Wl,--whole-archive" log "-Wl,--no-whole-archive")
#target_link_libraries(sdk 
# "-Wl,--whole-archive" #之后的库使用--whole-archive选项
# sdk_api
# sdk_dev 
#sdk_sys 
#"-Wl,--no-whole-archive")  #之后的库不使用--whole-archive选项
set_target_properties(rand PROPERTIES CLEAN_DIRECT_OUTPUT 1)
##set_target_properties(log PROPERTIES VERSION 1.0 SOVERSION 1)
install(TARGETS rand LIBRARY DESTINATION ${LIBRARY_OUTPUT_PATH})
#add_definitions(-DINFO)
link_directories(../../libs)
#link_libraries(liblog.a)
#link_libraries(libaes.a)
add_library(rand_static STATIC ${RAND_SRC})
target_link_libraries(rand_static aes)
#target_link_libraries(rand_static "-Wl,--whole-archive" aes "-Wl,--no-whole-archive")
set_target_properties(rand_static PROPERTIES OUTPUT_NAME rand)
set_target_properties(rand_static PROPERTIES CLEAN_DIRECT_OUTPUT 1)
install(TARGETS rand_static ARCHIVE DESTINATION ${LIBRARY_OUTPUT_PATH})
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