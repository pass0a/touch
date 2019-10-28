#cmake file for project association
#author: liuwenjun
#created:2014/02/20

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

## 添加项目
include_directories(${PROJECT_SOURCE_DIR}/output/include)
LINK_DIRECTORIES (${PROJECT_SOURCE_DIR}/output/lib)

if(PASSOA_COMPILER_MSVC)
ADD_EXECUTABLE(pngtest
${PROJECT_SOURCE_DIR}/test/cpp/pngtest.cpp
${PROJECT_SOURCE_DIR}/src/png.cpp
)
target_link_libraries(pngtest
debug gtestd
optimized gtest
libpng16_static.lib
zlibstatic.lib
)
else()
include_directories(${Boost_INCLUDE_DIR})
LINK_DIRECTORIES (${Boost_LIB_DIR})
ADD_EXECUTABLE(duktest
${PROJECT_SOURCE_DIR}/test/cpptest/arm.gcc.index.cpp
)
target_link_libraries(duktest
${Boost_LIBs})
endif()
