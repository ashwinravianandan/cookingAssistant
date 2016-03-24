cmake_minimum_required( VERSION 2.6 )

set( CMAKE_CXX_FLAGS "-std=c++1y")
set (SOURCE 
   ${SOURCE} 
   ${CMAKE_CURRENT_SOURCE_DIR}/Meal.h
   ${CMAKE_CURRENT_SOURCE_DIR}/MealBuilder.h
   ${CMAKE_CURRENT_SOURCE_DIR}/Meal.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/MealBuilder.cpp
   PARENT_SCOPE
   )

