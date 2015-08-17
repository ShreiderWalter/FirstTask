include_directories("${PROJECT_SOURCE_DIR}/CommonLib")

set (HEADERS 
"Client.h"
"stdafx.h"
)

set (SOURCES
"Client.cpp"
"main.cpp"
)

source_group("Header files" FILES ${HEADERS})

source_group("Source files" FILES ${SOURCES})

set (PROJECT_CONTENT ${SOURCES} ${HEADERS})

add_executable (Client ${PROJECT_CONTENT})

target_link_libraries(Client LIB)

set_property(TARGET Client PROPERTY FOLDER "executables")

set_target_properties(Client PROPERTIES LINK_FLAGS_DEBUG "/SUBSYSTEM:WINDOWS")

set_target_properties(Client PROPERTIES COMPILE_DEFINITIONS_DEBUG "_WINDOWS")

set_target_properties(Client PROPERTIES LINK_FLAGS_RELWITHDEBINFO "/SUBSYSTEM:WINDOWS")

set_target_properties(Client PROPERTIES COMPILE_DEFINITIONS_RELWITHDEBINFO "_WINDOWS")

set_target_properties(Client PROPERTIES LINK_FLAGS_RELEASE "/SUBSYSTEM:WINDOWS")

set_target_properties(Client PROPERTIES LINK_FLAGS_MINSIZEREL "/SUBSYSTEM:WINDOWS")

install (TARGETS Client RUNTIME DESTINATION ${PROJECT_BINARY_DIR}/bin)