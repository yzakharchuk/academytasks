SET(EXECUTABLE_SOURCES main.cpp)
ADD_EXECUTABLE(plugins_cli ${EXECUTABLE_SOURCES})
TARGET_INCLUDE_DIRECTORIES(plugins_cli 
    PUBLIC "${PROJECT_SOURCE_DIR}/include"
)
TARGET_LINK_LIBRARIES(plugins_cli)

SET_TARGET_PROPERTIES(plugins_cli
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)