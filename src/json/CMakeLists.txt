cmake_minimum_required( VERSION 2.6 )

set( CMAKE_CXX_FLAGS "-std=c++1y")
set (SOURCE 
   ${SOURCE} 
   ${CMAKE_CURRENT_SOURCE_DIR}/jsoncpp.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/json-forwards.h
   ${CMAKE_CURRENT_SOURCE_DIR}/json.h
   PARENT_SCOPE
   )

