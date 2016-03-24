cmake_minimum_required( VERSION 2.6 )

add_subdirectory( "${CMAKE_CURRENT_SOURCE_DIR}/Database" )
add_subdirectory( "${CMAKE_CURRENT_SOURCE_DIR}/json" )
add_subdirectory( "${CMAKE_CURRENT_SOURCE_DIR}/Generator" )
add_subdirectory( "${CMAKE_CURRENT_SOURCE_DIR}/Meal" )
add_subdirectory( "${CMAKE_CURRENT_SOURCE_DIR}/UserInterface" )

include_directories( "${CMAKE_CURRENT_SOURCE_DIR}/json" 
   "${CMAKE_CURRENT_SOURCE_DIR}/Database"  
   "${CMAKE_CURRENT_SOURCE_DIR}"  
   "${CMAKE_CURRENT_SOURCE_DIR}/Meal"  
   "${CMAKE_CURRENT_SOURCE_DIR}/UserInterface"  
   "${CMAKE_CURRENT_SOURCE_DIR}/Generator"  )

set( CMAKE_CXX_FLAGS "-std=c++1y")

set (SOURCE ${SOURCE}  main.cpp   )


add_executable( chef ${SOURCE}) 

install (TARGETS chef DESTINATION bin)
