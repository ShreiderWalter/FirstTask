include_directories("${PROJECT_SOURCE_DIR}/CommonLib")

file (GLOB CLIENT_SOURCES	"*.h"
				"*.cpp")

source_group("" FILES ${CLIENT_SOURCES})

add_executable (Client ${CLIENT_SOURCES})

target_link_libraries(Client LIB)

set_property(TARGET Client PROPERTY FOLDER "executables")

install (TARGETS Client RUNTIME DESTINATION ${PROJECT_BINARY_DIR}/bin)