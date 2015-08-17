include_directories("${PROJECT_SOURCE_DIR}/CommonLib")

set (HEADERS 
"Server.h"
"stdafx.h"
)

set (SOURCES
"Server.cpp"
"main.cpp"
)

source_group("Header files" FILES ${HEADERS})

source_group("Source files" FILES ${SOURCES})

set (PROJECT_CONTENT ${SOURCES} ${HEADERS})

add_executable (Server ${PROJECT_CONTENT})

target_link_libraries(Server LIB)

set_property(TARGET Server PROPERTY FOLDER "executables")

install (TARGETS Server RUNTIME DESTINATION ${PROJECT_BINARY_DIR}/bin)