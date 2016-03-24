cmake_minimum_required( VERSION 2.6 )

set( CMAKE_CXX_FLAGS "-std=c++1y")
set (SOURCE 
   ${SOURCE} 
   ${CMAKE_CURRENT_SOURCE_DIR}/GroceryListPrinter.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/MealMenuPrinter.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/MealMenuPrinter.h
   ${CMAKE_CURRENT_SOURCE_DIR}/OptionsHandler.h
   ${CMAKE_CURRENT_SOURCE_DIR}/GroceryListPrinter.h
   ${CMAKE_CURRENT_SOURCE_DIR}/OptionsHandler.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/Print.h
   PARENT_SCOPE
   )

