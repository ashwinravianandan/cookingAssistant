cmake_minimum_required( VERSION 2.6 )

set( CMAKE_CXX_FLAGS "-std=c++1y")
set (SOURCE 
   ${SOURCE} 
   ${CMAKE_CURRENT_SOURCE_DIR}/Database.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/Database.h 
   ${CMAKE_CURRENT_SOURCE_DIR}/TagDB.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/MealDB.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/TagDB.h 
   ${CMAKE_CURRENT_SOURCE_DIR}/MealDB.h 
   PARENT_SCOPE
   )

