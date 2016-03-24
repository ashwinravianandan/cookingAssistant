cmake_minimum_required( VERSION 2.6 )

set( CMAKE_CXX_FLAGS "-std=c++1y")
set (SOURCE 
   ${SOURCE} 
   ${CMAKE_CURRENT_SOURCE_DIR}/ListGenerator.h
   ${CMAKE_CURRENT_SOURCE_DIR}/MealGenerator.h
   ${CMAKE_CURRENT_SOURCE_DIR}/ListGenerator.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/MealGenerator.cpp
   PARENT_SCOPE
   )

