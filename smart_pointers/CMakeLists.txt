CMAKE_MINIMUM_REQUIRED(VERSION 3.10)
PROJECT(smart_pointers VERSION 1.0 LANGUAGES CXX)
SET(CMAKE_CXX_STANDARD 20)
ADD_COMPILE_OPTIONS(                  
        /W4
)

# Using standard-only C++ features
IF(NOT CMAKE_CXX_EXTENSIONS)
    SET(CMAKE_CXX_EXTENSIONS OFF)
ENDIF()

SET(EXECUTABLE_SOURCES 
    src/main.cpp
    src/test1.cpp
    src/test2.cpp
)

ADD_EXECUTABLE(smart_pointers ${EXECUTABLE_SOURCES})
SET_TARGET_PROPERTIES(smart_pointers
    PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

TARGET_INCLUDE_DIRECTORIES(smart_pointers 
    PUBLIC "${CMAKE_CURRENT_LIST_DIR}/include"
)