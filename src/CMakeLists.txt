
project(suuri)

set(SOURCES
	"big-int.h"
    "big-int.cpp"
    "suurimath.h" 
    "suurimath.cpp"
    "suuri-typetraits.h" 
    "big-float.h" 
    "big-float.cpp"
)

add_library(${PROJECT_NAME} STATIC ${SOURCES})

set_target_properties(${PROJECT_NAME} 
    PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
)