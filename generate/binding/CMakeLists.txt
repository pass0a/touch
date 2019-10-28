#cmake file for project association
#author: liuwenjun
#created:2014/02/20

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

## 添加项目
set(CMAKE_SHARED_LIBRARY_SUFFIX ".passoa")
SET(CMAKE_SHARED_LIBRARY_PREFIX "")
if(MSVC)
  
else()
  add_library(touch SHARED
	${PROJECT_SOURCE_DIR}/binding/touch.cpp
	${PROJECT_SOURCE_DIR}/src/touch.cpp
	)
  
  install(TARGETS touch
	LIBRARY DESTINATION ./node_modules/touch)
endif()
