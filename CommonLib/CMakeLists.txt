file (GLOB LIB_SOURCES	"*.h"
				"*.cpp")

source_group("" FILES ${LIB_SOURCES})

include_directories(.)

add_library (LIB SHARED ${LIB_SOURCES})

set_property(TARGET LIB PROPERTY FOLDER "libraries")

install (TARGETS LIB RUNTIME DESTINATION ${PROJECT_BINARY_DIR}/bin
		     LIBRARY DESTINATION ${PROJECT_BINARY_DIR}/bin)