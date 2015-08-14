include_directories("${PROJECT_SOURCE_DIR}/CommonLib")

file (GLOB SERVER_SOURCES	"*.h"
				"*.cpp")

source_group("" FILES ${SERVER_SOURCES})

add_executable (Server ${SERVER_SOURCES})

target_link_libraries(Server LIB)

set_property(TARGET Server PROPERTY FOLDER "executables")

install (TARGETS Server RUNTIME DESTINATION ${PROJECT_BINARY_DIR}/bin)