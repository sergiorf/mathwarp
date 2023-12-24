#####################################
# Define Target Information
#####################################
set(TARGET_NAME mathwarp-core)
set(TARGET_INCLUDE_FOLDER ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(TARGET_SOURCES 
  ${CMAKE_CURRENT_SOURCE_DIR}/src/evaluation.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/parser.cpp
)
set(TARGET_HEADERS 
    ${CMAKE_CURRENT_SOURCE_DIR}/include/evaluation.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/parser.h
)

set(TARGET_FILES ${TARGET_SOURCES} ${TARGET_HEADERS})

#####################################
# Support IDE Visualization
#####################################
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${TARGET_FILES})

#####################################
# Define Target according to options
#####################################
if(BUILD_SHARED_LIBS)
  add_library(${TARGET_NAME} SHARED ${TARGET_FILES})
else()
  add_library(${TARGET_NAME} STATIC ${TARGET_FILES})
endif()

#####################################
# Define Target Properties and Optional OpenSSL Dependency
#####################################

# generate an export header to expose symbols when using the library
generate_export_header(${TARGET_NAME} EXPORT_FILE_NAME ${CMAKE_BINARY_DIR}/exports/${TARGET_NAME}_export.h)

# add target properties such as debug postfix, MSVC Runtime and library version
set_target_properties(${TARGET_NAME} PROPERTIES 
                                      DEBUG_POSTFIX "-d" 
                                      MSVC_RUNTIME_LIBRARY "${MSVC_RUNTIME_TYPE}" 
                                      VERSION ${CMAKE_PROJECT_VERSION}
                                      SOVERSION ${CMAKE_PROJECT_VERSION})

# set target compile options as defined in the cmake/compiler_options.cmake Module
target_compile_options(${TARGET_NAME} PRIVATE ${compiler_options})

# add compiler definition WITH_OPENSSL, if found
target_compile_definitions(${TARGET_NAME} PRIVATE ${compiler_definitions} $<$<BOOL:${OPENSSL_FOUND}>:WITH_OPENSSL>)

# set target link options as defined in the cmake/compiler_options.cmake Module
target_link_options(${TARGET_NAME} PRIVATE ${linker_flags})

# include all the necessary directories
target_include_directories(${TARGET_NAME}
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/exports>
    $<INSTALL_INTERFACE:include>
    ${TARGET_INCLUDE_FOLDER}
  PRIVATE
    # include OpenSSL directories if present
    $<$<BOOL:${OPENSSL_FOUND}>:${OPENSSL_INCLUDE_DIR}>
    # Any other extra include required
)

message("CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}")
message("TARGET_NAME: ${TARGET_NAME}")
find_package(OpenSSL REQUIRED)
message("OpenSSL found: ${OpenSSL_FOUND}")

# link OpenSSL libraries if present
if(OPENSSL_FOUND)
  message("OpenSSL include directory: ${OpenSSL_INCLUDE_DIRS}")
  target_link_libraries(${TARGET_NAME} PUBLIC OpenSSL::SSL OpenSSL::Crypto)
  message("Linked with OpenSSL libraries")
  message("Compiler options: ${CMAKE_CXX_FLAGS}")
  message("Linker flags: ${CMAKE_EXE_LINKER_FLAGS}")
endif()

if(BUILD_TESTING)
  find_package(doctest REQUIRED)
  if(doctest_FOUND)

  endif()
  list(APPEND TEST_CASES
#    hellolib_test
  )
  foreach(TEST_CASE ${TEST_CASES})
    add_executable(${TEST_CASE} ${CMAKE_CURRENT_SOURCE_DIR}/test/${TEST_CASE}.cpp)
    target_link_libraries(${TEST_CASE} PRIVATE ${TARGET_NAME} doctest::doctest)
    target_compile_options(${TEST_CASE} PRIVATE ${compiler_options})
    target_compile_definitions(${TEST_CASE} PRIVATE ${compiler_definitions} $<$<BOOL:${OPENSSL_FOUND}>:WITH_OPENSSL>)
    target_link_options(${TEST_CASE} PRIVATE ${linker_flags})

    target_include_directories(${TEST_CASE}
      PUBLIC
        $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/exports>
      PRIVATE 
        ${TARGET_INCLUDE_FOLDER}
    )

    add_test(NAME ${TEST_CASE} COMMAND ${TEST_CASE})
  endforeach(TEST_CASE ${TEST_CASES})
endif()