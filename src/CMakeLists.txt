# Activate Testing, if given
if(BUILD_TESTING)
  enable_testing()
endif()

#####################################
# Define Targets
#####################################
add_subdirectory(mathwarp-core)
add_subdirectory(mathwarp-repl)

#####################################
# Define Install Targets
#####################################
install(TARGETS
  mathwarp-core
  mathwarp-repl
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  PUBLIC_HEADER DESTINATION include
)

install(
  FILES 
    ${CMAKE_SOURCE_DIR}/project/mathwarp-core/include/evaluation.h 
    ${CMAKE_BINARY_DIR}/exports/mathwarp-core_export.h
  DESTINATION 
    include/mathwarp-core)

install(FILES  
  ${CMAKE_SOURCE_DIR}/LICENSE
DESTINATION .)