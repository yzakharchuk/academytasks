SET(SOURCE_LIB src/kangaroo.cpp)
ADD_LIBRARY(kangaroo SHARED ${SOURCE_LIB})
TARGET_INCLUDE_DIRECTORIES(kangaroo  
    PUBLIC "${PROJECT_SOURCE_DIR}/include"           # ABSTRACT CLASS INTERFACE 
    PUBLIC "${CMAKE_CURRENT_LIST_DIR}/include"       # OWN LIBRARY INTERFACE
)

SET_TARGET_PROPERTIES(kangaroo
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)
